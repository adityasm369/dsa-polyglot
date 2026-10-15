# 12 — Dynamic programming

## The idea in one line

Solve each subproblem once, and reuse the answer. Exponential work collapses to
polynomial because the same subproblems keep recurring.

## How to recognise it

- The problem asks for a **count, minimum, maximum or existence** over choices.
- A naive recursion re-solves the same smaller question many times.
- The answer for size n is built from answers for smaller sizes.

## The ladder every problem climbs

| step | technique | complexity |
|---|---|---|
| 1 | naive recursion | exponential time, O(n) stack |
| 2 | memoised recursion | O(n) time, O(n) space |
| 3 | tabulation (bottom-up array) | O(n) time, O(n) space |
| 4 | keep only the last few values | **O(n) time, O(1) space** |

Make students walk the ladder on every problem. Step 1 is correct and useless
past n ≈ 40. Step 4 is usually the one they are asked for in an interview.

## Problems in this pattern

| | problem | difficulty | why it is here |
|---|---|---|---|
| 1 | [climbing-stairs](climbing-stairs/) | basic | the whole ladder on one small recurrence |
