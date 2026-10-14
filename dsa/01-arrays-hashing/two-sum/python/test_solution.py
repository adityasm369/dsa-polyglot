"""Tests written from SPEC.md, before the solution. Run: python3 -m unittest -v"""
import unittest
from naive import two_sum_naive
from solution import two_sum

CASES = [
    ("minimum size",          [1, 2],                 3,           (0, 1)),
    ("answer at the ends",    [3, 2, 4, 1],           4,           (0, 3)),
    ("duplicate values",      [3, 3],                 6,           (0, 1)),
    ("same value, one pair",  [3, 2, 3],              6,           (0, 2)),
    ("negatives",             [-1, -2, -3, -4],       -6,          (1, 3)),
    ("zero target and zeros", [0, 0],                 0,           (0, 1)),
    ("overflow guard",        [10**9, 10**9],         2 * 10**9,   (0, 1)),
    ("answer in the middle",  [1, 5, 2, 7, 3],        9,           (2, 3)),
]


class TwoSum(unittest.TestCase):
    def test_spec_cases(self):
        for name, nums, target, want in CASES:
            with self.subTest(name):
                self.assertEqual(two_sum(list(nums), target), want)

    def test_indices_are_ordered_and_distinct(self):
        for name, nums, target, _ in CASES:
            i, j = two_sum(list(nums), target)
            self.assertLess(i, j, name)

    def test_indices_point_at_the_sum(self):
        for name, nums, target, _ in CASES:
            i, j = two_sum(list(nums), target)
            self.assertEqual(nums[i] + nums[j], target, name)

    def test_input_is_not_modified(self):
        nums = [3, 2, 4, 1]
        two_sum(nums, 4)
        self.assertEqual(nums, [3, 2, 4, 1])

    def test_no_pair_returns_none(self):
        # Not in the spec's constraints, so the behaviour is pinned here rather
        # than left to whatever the code happens to do.
        self.assertIsNone(two_sum([1, 2, 3], 100))

    def test_naive_agrees_with_the_fast_one(self):
        for name, nums, target, _ in CASES:
            self.assertEqual(two_sum(list(nums), target),
                             two_sum_naive(list(nums), target), name)


if __name__ == "__main__":
    unittest.main(verbosity=2)
