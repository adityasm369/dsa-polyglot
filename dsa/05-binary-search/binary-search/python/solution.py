"""binary-search. Time O(log n), Space O(1).

Python integers are arbitrary precision, so (lo + hi) // 2 CANNOT overflow here
-- this is one of the three languages in the repo immune to the JDK bug. The
safe form is used anyway, because the habit is what transfers to the languages
where it matters.
"""
from typing import List


def search(nums: List[int], target: int) -> int:
    lo, hi = 0, len(nums) - 1
    while lo <= hi:                     # <=, not <: [5] must be searchable
        # lo + (hi - lo) // 2, not (lo + hi) // 2. Harmless in Python; the same
        # line in Java wrapped negative and broke java.util.Arrays for 9 years.
        mid = lo + (hi - lo) // 2
        if nums[mid] == target:
            return mid
        if nums[mid] < target:
            lo = mid + 1                # mid is ruled out, so +1 -- invariant 1
        else:
            hi = mid - 1                # and -1 here, for the same reason
    return -1


def search_counting(nums: List[int], target: int):
    """Same algorithm, returning the iteration count. For the lesson in
    teaching note 2: run it on 10,000 elements and read the number."""
    lo, hi, steps = 0, len(nums) - 1, 0
    while lo <= hi:
        steps += 1
        mid = lo + (hi - lo) // 2
        if nums[mid] == target:
            return mid, steps
        if nums[mid] < target:
            lo = mid + 1
        else:
            hi = mid - 1
    return -1, steps
