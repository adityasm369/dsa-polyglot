import unittest
from solution import is_valid

CASES = [
    ("single opener", "(", False),
    ("single closer", ")", False),
    ("simple", "()", True),
    ("all three types", "()[]{}", True),
    ("nested", "([{}])", True),
    ("interleaved", "([)]", False),
    ("closes too early", ")(", False),
    ("left open", "(((", False),
    ("long balanced", "(" * 5000 + ")" * 5000, True),
]


class ValidParentheses(unittest.TestCase):
    def test_spec_cases(self):
        for name, s, want in CASES:
            with self.subTest(name):
                self.assertEqual(is_valid(s), want)

    def test_counting_is_not_enough(self):
        # Equal counts of each bracket, wrong nesting: a counter says true.
        self.assertFalse(is_valid("([)]"))

    def test_input_not_modified(self):
        s = "([{}])"
        is_valid(s)
        self.assertEqual(s, "([{}])")


if __name__ == "__main__":
    unittest.main(verbosity=2)
