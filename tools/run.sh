#!/usr/bin/env bash
# Run the tests for one language, or all seven.
#
#   tools/run.sh                      every language, every problem
#   tools/run.sh python               one language, every problem
#   tools/run.sh all two-sum          every language, one problem
#   tools/run.sh rust two-sum
#
# Exits non-zero if anything fails, so CI and a pre-commit hook can both use it.
set -uo pipefail
cd "$(dirname "$0")/.."
ROOT=$PWD
LANG_FILTER=${1:-all}
PROB_FILTER=${2:-}
PASS=0; FAIL=0; SKIP=0; TODO=0
declare -a FAILED=()

have() { command -v "$1" >/dev/null 2>&1; }

# True when the output shows a suite that ran nothing.
zero_tests() {
  local lang=$1 out=$2
  case $lang in
    javascript) grep -qE "^# tests 0$"            <<<"$out" ;;
    python)     grep -qE "^Ran 0 tests"           <<<"$out" ;;
    go)         grep -qE "no test files"          <<<"$out" ;;
    rust)       grep -qE "running 0 tests"        <<<"$out" ;;
    c|cpp|java) grep -qE "  0 checks passed"      <<<"$out" ;;
    *)          return 1 ;;
  esac
}

run_one() {           # run_one <lang> <dir> <label>
  local lang=$1 dir=$2 label=$3 out rc
  # An empty language folder is work not yet done, which is different from work
  # that is broken. It is reported as TODO and does not fail the suite;
  # specs/PROGRESS.md is what tracks completeness.
  if ! ls "$dir"/* >/dev/null 2>&1; then
    printf "  \033[33mTODO\033[0m %s (not implemented yet)\n" "$label"
    TODO=$((TODO+1)); return
  fi
  case $lang in
    python)     have python3 || { echo "  SKIP $label (no python3)"; SKIP=$((SKIP+1)); return; }
                out=$(cd "$dir" && python3 -m unittest -q 2>&1); rc=$? ;;
    c)          have gcc || { echo "  SKIP $label (no gcc)"; SKIP=$((SKIP+1)); return; }
                out=$(cd "$dir" && make -s test 2>&1); rc=$? ;;
    cpp)        have g++ || { echo "  SKIP $label (no g++)"; SKIP=$((SKIP+1)); return; }
                out=$(cd "$dir" && make -s test 2>&1); rc=$? ;;
    java)       have javac || { echo "  SKIP $label (no javac)"; SKIP=$((SKIP+1)); return; }
                out=$(cd "$dir" && javac -d /tmp/ts_java_$$ ./*.java 2>&1 && \
                      java -cp /tmp/ts_java_$$ "$(basename "$(ls ./*Test.java | head -1)" .java)" 2>&1); rc=$?
                rm -rf /tmp/ts_java_$$ ;;
    javascript) have node || { echo "  SKIP $label (no node)"; SKIP=$((SKIP+1)); return; }
                # The test file is named solution.test.js because that is what
                # `node --test` discovers. It was test_solution.js, which
                # matches NONE of Node's default patterns -- so the runner found
                # zero files, ran nothing, and exited 0. A suite that reports
                # success having run nothing is worse than a failing one, which
                # is why zero_tests below treats it as a failure.
                out=$(cd "$dir" && node --test 2>&1); rc=$? ;;
    go)         have go || { echo "  SKIP $label (no go)"; SKIP=$((SKIP+1)); return; }
                out=$(cd "$dir" && go test ./... 2>&1); rc=$? ;;
    rust)       have rustc || { echo "  SKIP $label (no rustc)"; SKIP=$((SKIP+1)); return; }
                out=$(cd "$dir" && make -s test 2>&1); rc=$? ;;
    *)          return ;;
  esac
  # A green run that executed nothing is a false green. Every harness here
  # prints its count; if the count is zero, fail.
  if [ "$rc" -eq 0 ] && zero_tests "$lang" "$out"; then
    printf "  \033[31mFAIL\033[0m %s (ran 0 tests)\n" "$label"
    FAIL=$((FAIL+1)); FAILED+=("$label: 0 tests"); return
  fi
  if [ "$rc" -eq 0 ]; then
    printf "  \033[32mPASS\033[0m %s\n" "$label"; PASS=$((PASS+1))
  else
    printf "  \033[31mFAIL\033[0m %s\n" "$label"; FAIL=$((FAIL+1)); FAILED+=("$label")
    echo "$out" | sed 's/^/        /' | tail -12
  fi
}

echo "dsa-polyglot — running tests"
echo
for pattern in dsa/*/; do
  [ -d "$pattern" ] || continue
  for problem in "$pattern"*/; do
    [ -f "$problem/SPEC.md" ] || continue
    pname=$(basename "$problem")
    [ -n "$PROB_FILTER" ] && [ "$pname" != "$PROB_FILTER" ] && continue
    echo "$(basename "$pattern")/$pname"
    for lang in c cpp java python javascript go rust; do
      [ -d "$problem$lang" ] || continue
      [ "$LANG_FILTER" != "all" ] && [ "$LANG_FILTER" != "$lang" ] && continue
      run_one "$lang" "$ROOT/$problem$lang" "$lang"
    done
    echo
  done
done

echo "────────────────────────────────────────"
printf "  %d passed, %d failed, %d skipped, %d not yet written\n" \
       "$PASS" "$FAIL" "$SKIP" "$TODO"
[ "$FAIL" -gt 0 ] && { printf "  failed: %s\n" "${FAILED[*]}"; exit 1; }
exit 0
