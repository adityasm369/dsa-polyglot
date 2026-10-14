"""valid-palindrome. Time O(n), Space O(1).

Python's str is a sequence of CODE POINTS, so s[i] is a character and not a
byte -- the only language here besides Rust where "the i-th character" means
what a beginner expects. That is also why the one-liner below is so tempting.
"""


def is_palindrome(s: str) -> bool:
    i, j = 0, len(s) - 1
    while i < j:
        # Each skip re-checks i < j. Without it, "...,!" walks both pointers
        # off the end -- the single most common bug in this problem.
        while i < j and not s[i].isalnum():
            i += 1
        while i < j and not s[j].isalnum():
            j -= 1
        if s[i].lower() != s[j].lower():
            return False
        i += 1
        j -= 1
    return True


def is_palindrome_naive(s: str) -> bool:
    """The answer everyone writes first. Correct, O(n) time -- and O(n) SPACE:
    it builds a filtered string and then a reversed copy of it. Kept because
    comparing the two is the lesson (specs/0001 rule 5)."""
    t = [c.lower() for c in s if c.isalnum()]
    return t == t[::-1]
