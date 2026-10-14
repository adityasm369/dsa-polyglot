"""two-sum — one pass, hash of value -> index.

Time  O(n)   each element is inserted and looked up once
Space O(n)   the map holds at most n entries

Python cannot overflow here: ints are arbitrary precision, so `target - x` is
exact for any input the spec allows. That is a real advantage and it is worth
naming, because the same line is a bug in C, C++ and Java.
"""
from typing import Dict, List, Optional, Tuple


def two_sum(nums: List[int], target: int) -> Optional[Tuple[int, int]]:
    seen: Dict[int, int] = {}          # value -> the index it was seen at
    for j, x in enumerate(nums):
        # Look BEFORE inserting. Everything in `seen` is at an index < j, which
        # gives i < j for free and makes it impossible to pair x with itself.
        i = seen.get(target - x)
        if i is not None:
            return (i, j)
        # Written only if absent: on duplicates the FIRST index must win, so
        # that [3, 3] returns (0, 1) rather than (1, 1).
        seen.setdefault(x, j)
    return None
