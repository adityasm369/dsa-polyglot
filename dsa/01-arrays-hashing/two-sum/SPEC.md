# two-sum

- **Pattern:** 01 — arrays and hashing
- **Difficulty:** basic
- **Written:** before any code in this folder, as specs/0001 requires

## Problem

Given an array of integers `nums` and an integer `target`, return the indices
of the two numbers that add up to `target`.

## Contract

```
input   nums: array of int, target: int
output  (i, j) with i < j and nums[i] + nums[j] == target
        exactly one such pair is guaranteed to exist
        the same element may not be used twice
```

## Constraints

```
2 <= len(nums) <= 10^4
-10^9 <= nums[i] <= 10^9
-10^9 <= target  <= 10^9
exactly one valid answer exists
```

Two constraints decide the implementation and must be read carefully:

- **Values reach ±10⁹.** `nums[i] + nums[j]` can reach ±2×10⁹, which **overflows
  a signed 32-bit integer**. In C, C++ and Java the accumulator must be 64-bit.
  In Python it cannot overflow. In Rust it panics in debug and wraps in release
  unless you say otherwise. This single line is why the same algorithm is not
  the same program in seven languages.
- **Exactly one answer exists.** So no "not found" case is specified. The tests
  still assert the behaviour each implementation chose, because "undefined" in
  a spec becomes "whatever it happened to do" in a classroom.

## Invariants

1. The returned indices are **distinct** and **ordered**: `i < j`.
2. The indices are into the **original** array. If an implementation sorts, it
   must map back, and the tests check an unsorted input with the answer at the
   ends.
3. The input array is **not modified**. Asserted in the languages where it can
   be (C, C++, Java, Go, Rust).

## Complexity target

| | time | space | note |
|---|---|---|---|
| naive | O(n²) | O(1) | kept in `python/naive.py` because the comparison is the lesson |
| **required** | **O(n)** | **O(n)** | one pass, hash of value → index |

Rejected on purpose: sort-then-two-pointer is O(n log n) time and O(n) space
once you keep the original indices. It is *worse on both axes* here, and it is
the answer most students give first. The spec records the rejection so the
teaching note has something to point at.

## The one-pass insight

The obvious hash solution fills the map, then searches it: two passes. One pass
is enough, because when you reach index `j` you only need a partner **before**
it — and every index before `j` is already in the map. Looking up
`target - nums[j]` before inserting `nums[j]` also handles the
"same element twice" rule for free: the element is not in the map yet, so it
cannot match itself.

## Edge cases the tests must cover

| case | input | why it breaks naive code |
|---|---|---|
| answer at the ends | `[3,2,4,1], 4` → `(0,3)` | fails if you return the first partial match |
| duplicate values | `[3,3], 6` → `(0,1)` | fails if the map is keyed without care |
| the same value twice, only one valid | `[3,2,3], 6` → `(0,2)` | fails if you match an element with itself |
| negatives | `[-1,-2,-3,-4], -6` → `(1,3)` | fails on unsigned or `abs` assumptions |
| zero target, zero values | `[0,0], 0` → `(0,1)` | fails on falsy checks (JavaScript especially) |
| **overflow** | `[10^9, 10^9], 2×10^9` → `(0,1)` | **fails in C/C++/Java with a 32-bit sum** |
| minimum size | `[1,2], 3` → `(0,1)` | fails on loops that assume n > 2 |

## Teaching notes

1. Ask for the brute force first and **time it** on n = 10⁴. The nested loop is
   ~5×10⁷ comparisons; let them watch it take a second in Python and 40 ms in
   C++. That contrast is worth an hour of complexity theory.
2. Then ask: *what question is the inner loop asking?* Lead them to "have I seen
   `target - x`?" and the hash table arrives on its own.
3. Ask what happens with `[10^9, 10^9]`. Most will not see it. Run it in Java
   and show the negative sum. This is the moment the constraints section of a
   problem statement stops being decoration.
4. Finish on the C implementation. They have used a hash map all year; have them
   read 60 lines of one.

## Common mistakes

- Returning values instead of indices.
- Building the map first, then searching — correct, but two passes; ask why one
  is enough.
- Using the same element twice (`[3,2,3]`, target 6 → returning `(0,0)`).
- 32-bit overflow on the sum.
- In JavaScript, `if (map[complement])` instead of `map.has(complement)` — index
  `0` is falsy, so `[0,0], 0` silently fails.
- In Rust, reaching for `.unwrap()` on the lookup and panicking on a miss.
