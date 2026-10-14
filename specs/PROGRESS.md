# Progress

Honest status. A pattern is **complete** only when every problem in it has a
spec, tests and seven passing implementations. Anything else says so.

Last verified by running `tools/run.sh`: **2026-10-14**, 7 passed, 0 failed.

## Patterns

| # | pattern | problems | status |
|---|---|---|---|
| 01 | arrays & hashing | two-sum ✅ · group-anagrams ⬜ · longest-consecutive ⬜ | **1 of 3 complete** |
| 02 | two pointers | — | not started |
| 03 | sliding window | — | not started |
| 04 | stack | — | not started |
| 05 | binary search | — | not started |
| 06 | linked list | — | not started |
| 07 | trees | — | not started |
| 08 | tries | — | not started |
| 09 | heap / priority queue | — | not started |
| 10 | backtracking | — | not started |
| 11 | graphs | — | not started |
| 12 | dynamic programming | — | not started |
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
