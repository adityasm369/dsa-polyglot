# climbing-stairs

- **Pattern:** 12 — dynamic programming
- **Difficulty:** basic
- **Written:** before any code in this folder

## Problem

You are climbing a staircase of n steps. Each move you can climb 1 or 2 steps.
Return the number of distinct ways to reach the top.

## Contract

```
input   n: integer
output  the number of distinct sequences of 1s and 2s that sum to n
```

## Constraints

```
1 <= n <= 45
```

The 45 is the trap. The answer for n = 45 is 1 836 311 903, which fits in a
32-bit int. The answer for n = 92 overflows a signed 64-bit int. The constraint
keeps students in the range where the naive version finishes but is visibly
slow, so the difference is measurable.

## Invariants

1. The recurrence: `ways(n) = ways(n-1) + ways(n-2)`, with `ways(1) = 1` and
   `ways(2) = 2`. The last step was either a 1 or a 2.
2. The answer for every n is **positive**. A function that returns 0 for some
   valid n has the base cases wrong.
3. Extra space for the required solution is **O(1)**.

## Complexity target

| | time | space | |
|---|---|---|---|
| naive recursion | O(2ⁿ) | O(n) | unusable past n ≈ 40 |
| memoised | O(n) | O(n) | correct |
| tabulated | O(n) | O(n) | correct |
| **required: two variables** | **O(n)** | **O(1)** | |

## Why the recurrence is Fibonacci

The last move was either a single step (from n−1) or a double step (from n−2),
and those two families of sequences do not overlap. Add the counts. Students
who recognise Fibonacci without this argument have memorised a sequence; students
who can state the argument can solve the next problem.

## Edge cases the tests must cover

| n | answer | what it breaks |
|---|---|---|
| 1 | 1 | base case off by one |
| 2 | 2 | base case off by one the other way |
| 3 | 3 | the first value the recurrence actually computes |
| 10 | 89 | a hand-checkable middle value |
| 45 | 1 836 311 903 | the largest allowed input; fits in int32 |

## Teaching notes

1. Ask for the recursive version and run it for n = 40, then n = 45. Time it.
   Let students watch it take seconds, then minutes if they push it. That gap is
   the whole motivation for the rest of the pattern.
2. Draw the recursion tree for n = 5. Count how many times `ways(2)` appears.
   Ask them what would happen if they stored the answer the first time.
3. Walk the ladder aloud, one rung at a time, on the same board.
4. Ask why the final version needs only two variables. Answer: each new value
   depends only on the previous two.

## Common mistakes

- Wrong base cases: `ways(0) = 0`, which makes every answer one too small.
- Using `int` for n = 45 in a language where it overflows at a different value
  (no problem at 45, but a student who generalises it will overflow later).
- Memoising with an array of size n when n + 1 is needed.
