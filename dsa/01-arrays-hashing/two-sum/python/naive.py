"""The O(n^2) version, kept deliberately.

specs/0001 rule 5: a wrong approach stays when the gap between it and the good
one is the lesson. Time this against solution.py on n = 10_000 before showing
the hash table -- roughly 5*10^7 comparisons, about a second in CPython.
"""
from typing import List, Optional, Tuple


def two_sum_naive(nums: List[int], target: int) -> Optional[Tuple[int, int]]:
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):      # j starts at i+1, never at 0:
            if nums[i] + nums[j] == target:    # that is what stops an element
                return (i, j)                  # pairing with itself
    return None
