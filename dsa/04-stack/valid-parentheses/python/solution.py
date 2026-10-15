"""valid-parentheses. Time O(n), Space O(n).

A list is the stack: append pushes, pop removes the top. Python's list is a
dynamic array, so both are amortised O(1).
"""

_PAIRS = {")": "(", "]": "[", "}": "{"}


def is_valid(s: str) -> bool:
    stack = []
    for ch in s:
        if ch in _PAIRS:                       # a closer
            # Must match the MOST RECENT unclosed opener, and one must exist.
            if not stack or stack.pop() != _PAIRS[ch]:
                return False
        else:                                  # an opener
            stack.append(ch)
    # An opener left open at the end is also invalid.
    return not stack
