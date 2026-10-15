"""climbing-stairs. Time O(n), Space O(1).

Python integers are arbitrary precision, so the answer cannot overflow for any
n. The other six languages here can, past n = 45 (int32) or n = 92 (int64).
"""


def climb_stairs(n: int) -> int:
    if n <= 2:
        return n                  # ways(1) = 1, ways(2) = 2
    prev, cur = 1, 2              # ways(1), ways(2)
    for _ in range(3, n + 1):
        prev, cur = cur, prev + cur   # the last move was a 1 or a 2
    return cur


def climb_naive(n: int) -> int:
    """The exponential recursion, kept deliberately. Correct, and unusable
    past n of about 35. Run it to show the ladder's first rung."""
    if n <= 2:
        return n
    return climb_naive(n - 1) + climb_naive(n - 2)
