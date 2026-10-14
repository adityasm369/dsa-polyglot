# 05 — Binary search

## The idea in one line

Halve the search space every step, so a million elements take twenty looks.

## How to recognise it

The data is **sorted**, or — and this is the part students miss — the *answer*
is monotonic even when the input is not. If "is X good enough?" is false for
everything below some threshold and true for everything above it, you can
binary-search the threshold.

Signals:
- "find the target in a sorted array"
- "find the first/last position of …"
- "the minimum capacity such that …" ← binary search on the **answer**
- "a rotated sorted array"

## What it costs

| | time | space |
|---|---|---|
| linear scan | O(n) | O(1) |
| binary search | **O(log n)** | O(1) iterative, O(log n) recursive |

Make the numbers concrete: 1 000 000 elements is 20 comparisons. 1 000 000 000
is 30. That is the whole reason databases keep indexes sorted.

## The bug this pattern is famous for

```
mid = (lo + hi) / 2        // WRONG
mid = lo + (hi - lo) / 2   // right
```

When `lo + hi` exceeds the integer type's range it overflows. In Java it wraps
negative and the array access throws; in C and C++ signed overflow is
**undefined behaviour**, so the compiler may do anything at all.

This is not a classroom curiosity. Jon Bentley published binary search in
*Programming Pearls* with this bug. Joshua Bloch found it in
`java.util.Arrays.binarySearch` in 2006 — it had been in the JDK since 1.2,
**nine years**, in a function every Java programmer trusted. Bloch's write-up is
titled *"Nearly All Binary Searches and Mergesorts Are Broken"*.

Three of the seven languages here are vulnerable, three are not, and one tells
you at runtime. The solutions say which is which, and the tests prove it.

## Why it is so hard to write correctly

Binary search is four lines and famously difficult. The difficulty is entirely
in the **loop invariant**: you must be able to say, at every iteration, exactly
which elements are still candidates. Get `lo <= hi` versus `lo < hi` wrong, or
`hi = mid` versus `hi = mid - 1`, and you get an infinite loop or an
off-by-one — and both pass a careless test.

Make your students state the invariant in words before they write the loop.
`binary-search/SPEC.md` states it as a numbered invariant for exactly that
reason.

## Problems in this pattern

| | problem | difficulty | why it is here |
|---|---|---|---|
| 1 | [binary-search](binary-search/) | basic | the invariant, and the overflow that fooled the JDK for nine years |
