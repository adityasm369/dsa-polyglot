"""Cases from SPEC.md. python3 -m unittest -v"""
import unittest
from solution import is_palindrome, is_palindrome_naive

CASES = [
    ("empty",                 "",                               True),
    ("one character",         "a",                              True),
    ("only punctuation",      ".,!",                            True),
    ("mixed case",            "Aa",                             True),
    ("digits count",          "0P",                             False),
    ("the textbook one",      "A man, a plan, a canal: Panama", True),
    ("nearly",                "race a car",                     False),
    ("all skipped but one",   "...a...",                        True),
    ("spaces only",           "   ",                            True),
    ("digits palindrome",     "12321",                          True),
    ("digits not",            "12345",                          False),
]


class ValidPalindrome(unittest.TestCase):
    def test_spec_cases(self):
        for name, s, want in CASES:
            with self.subTest(name):
                self.assertEqual(is_palindrome(s), want)

    def test_input_not_modified(self):
        s = "A man, a plan"
        is_palindrome(s)
        self.assertEqual(s, "A man, a plan")

    def test_naive_agrees(self):
        for name, s, _ in CASES:
            self.assertEqual(is_palindrome(s), is_palindrome_naive(s), name)

    def test_long_input(self):
        # 200k characters, the constraint's upper bound
        self.assertTrue(is_palindrome("ab" * 100000 + "ba" * 100000))


if __name__ == "__main__":
    unittest.main(verbosity=2)
