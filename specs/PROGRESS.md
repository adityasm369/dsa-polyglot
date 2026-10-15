# Progress

Honest status. A pattern is **complete** only when every problem in it has a
spec, tests and seven passing implementations. Anything else says so.

Last verified by running `tools/run.sh`: **2026-10-15**, 49 passed, 0 failed,
0 not yet written.

The eight folders scaffolded for problems 3-10 are **not counted at all**,
because `tools/run.sh` only walks a problem that has a `SPEC.md`. That is
deliberate and follows rule 1: without a spec it is not a problem yet, it is an
empty directory. (An earlier draft of this line claimed "56 TODO". It was
wrong -- the runner reports 0, for the reason just given.)

**A correction.** The first version of this file claimed 7 passing for
`two-sum`. One of those seven was a lie: `node --test` with no argument
discovers `*.test.js`, and the file was named `test_solution.js`, so the runner
found **zero files, ran nothing, and exited 0**. The files are now named
`solution.test.js`, and `tools/run.sh` fails any language whose output shows a
zero-test run -- a suite that reports success having executed nothing is worse
than one that fails.

## Patterns

| # | pattern | problems | status |
|---|---|---|---|
| 01 | arrays & hashing | two-sum ✅ · group-anagrams ⬜ · longest-consecutive ⬜ | **1 of 3 complete** |
| 02 | two pointers | valid-palindrome ✅ · trapping-rain-water ⬜ | **1 of 2 complete** |
| 03 | sliding window | longest-substring ⬜ | scaffolded |
| 04 | stack | valid-parentheses ✅ | **complete** |
| 05 | binary search | binary-search ✅ | **complete** |
| 06 | linked list | reverse-linked-list ✅ · linked-list-cycle ✅ | **complete** |
| 07 | trees | — | not started |
| 08 | tries | — | not started |
| 09 | heap / priority queue | — | not started |
| 10 | backtracking | — | not started |
| 11 | graphs | — | not started |
| 12 | dynamic programming | climbing-stairs ✅ | **complete** |
| 13 | greedy | — | not started |
| 14 | intervals | — | not started |
| 15 | bit manipulation | — | not started |

## What "complete" means for two-sum

| | |
|---|---|
| SPEC.md | contract, constraints, invariants, complexity target with the rejected alternative, 7 edge cases, teaching notes, common mistakes |
| tests | 7 languages, all spec cases plus invariant checks, input-immutability, the no-pair case and a 2000-key probe stress |
| C | hash table written from scratch — open addressing, linear probing, Knuth multiplicative hash. Clean under `-fsanitize=address,undefined` |
| teaching | the Java test prints the int32 wrap live; `naive.py` kept for timing |

## Honest gaps

- **One problem is finished, not fifteen.** The repo is built to grow one
  complete pattern at a time; `two-sum` is the proven template for the rest.
- **No benchmarks across languages yet.** Go has `BenchmarkTwoSum`; the other
  six do not have an equivalent, so no cross-language timing is published. Any
  such number would need the same input and the same machine to mean anything.
- **CI has not run yet** — it is committed but this repo has been pushed only
  once. The versions in the README are from the machine it was built on.
