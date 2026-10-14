# binary-search

- **Pattern:** 05 — binary search
- **Difficulty:** basic
- **Written:** before any code in this folder

## Problem

Given an array sorted in ascending order and a target, return the index of the
target, or -1 if it is absent.

## Contract

```
input   nums: array of int, sorted ascending, no duplicates
        target: int
output  the index of target in nums, or -1
```

## Constraints

```
0 <= len(nums) <= 10^4
-2^31 <= nums[i], target <= 2^31 - 1      <-- read this line twice
nums is sorted ascending with no duplicates
```

**The value range is the whole point of this problem.** Indices here are small,
so `lo + hi` cannot overflow from the *indices*. The constraint that matters is
on the array length in the general case — a 2-billion-element array is not
hypothetical on a 64-bit machine, and that is precisely the case Bloch found
broken in the JDK. The tests therefore check the arithmetic directly, not only
through a small array.

## Invariants

State these out loud before writing the loop. The algorithm is four lines and
every bug in it is an invariant violation.

1. **The answer, if it exists, is always inside `[lo, hi]`.** Every assignment
   to `lo` or `hi` must preserve this. `hi = mid - 1` is correct only because
   `nums[mid]` was just ruled out.
2. The search space **strictly shrinks** every iteration. If it can fail to
   shrink, the loop does not terminate. This is why `mid` must be computed so
   that `mid < hi` when `hi > lo`.
3. `nums` is **not modified**.
4. The returned index is `-1`, or a valid index with `nums[i] == target`.

## Complexity target

| | time | space | |
|---|---|---|---|
| linear scan | O(n) | O(1) | correct, and misses the point |
| recursive binary search | O(log n) | **O(log n)** | the stack frames are real space |
| **required** | **O(log n)** | **O(1)** | iterative |

## The overflow, by language

The same expression is a different kind of wrong in each:

| language | `lo + hi` overflowing a 32-bit int | what happens |
|---|---|---|
| C | signed overflow | **undefined behaviour** — the compiler may assume it cannot happen and delete your check |
| C++ | signed overflow | same, and `-fsanitize=undefined` will catch it |
| Java | silent wraparound | negative `mid`, then `ArrayIndexOutOfBoundsException` — **the JDK bug** |
| Go | silent wraparound (fixed-size ints) | `int` is 64-bit here, so it needs a far larger array to bite |
| Rust | **panics in debug**, wraps in release | the only language that tells you at runtime by default |
| Python | cannot overflow | arbitrary-precision integers |
| JavaScript | cannot overflow below 2^53 | doubles, so safe for any real array length |

Every solution in this folder uses `lo + (hi - lo) / 2`, and each says why in a
comment specific to its language.

## Edge cases the tests must cover

| case | input | expected | what it breaks |
|---|---|---|---|
| empty array | `[], 5` | -1 | loops that read `nums[0]` before checking |
| one element, present | `[5], 5` | 0 | `lo < hi` instead of `lo <= hi` — returns -1 |
| one element, absent | `[5], 3` | -1 | — |
| target is first | `[1,2,3,4,5], 1` | 0 | — |
| target is last | `[1,2,3,4,5], 5` | 4 | off-by-one on the upper bound |
| absent, below range | `[1,2,3], 0` | -1 | — |
| absent, above range | `[1,2,3], 9` | -1 | — |
| absent, in a gap | `[1,3,5,7], 4` | -1 | loops that fail to terminate |
| two elements | `[1,2], 2` | 1 | the classic non-shrinking-space infinite loop |
| negatives | `[-5,-3,-1], -3` | 1 | — |
| extreme values | `[INT_MIN, 0, INT_MAX], INT_MAX` | 2 | **the overflow case** |
| large array | 10 000 elements | every index findable | — |

## Teaching notes

1. Have them write it from memory, then run the tests. Most fail `[5], 5` or
   `[1,2], 2`. Both are invariant 1 or 2 violations, and naming which one is the
   lesson.
2. Add an iteration counter and print it for n = 10 000. Twenty. Then ask what
   it would be for a billion. Thirty. That is the moment O(log n) stops being
   notation.
3. Then tell them about Bloch and the JDK. Nine years, in code everybody
   trusted, found by someone writing a *different* binary search and checking
   his assumptions. Ask what else they trust.
4. Run the Rust test in debug and watch the overflow panic. Then `make release`
   and watch it wrap silently. Same code, different answer — which is the honest
   summary of the whole language comparison.

## Common mistakes

- `(lo + hi) / 2` — the famous one.
- `while (lo < hi)` when the body is written for `lo <= hi`: misses a
  single-element range.
- `hi = mid` with `lo <= hi`: the space stops shrinking and the loop hangs.
- Returning `lo` on failure instead of `-1` (that is `lower_bound`, a different
  function — useful, but not this spec).
- Recursing, and calling it O(1) space.
