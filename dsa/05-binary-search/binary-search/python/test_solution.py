"""Cases from SPEC.md."""
import math
import unittest
from solution import search, search_counting

INT_MIN, INT_MAX = -2**31, 2**31 - 1
CASES = [
    ("empty array",        [],              5,       -1),
    ("one element present", [5],            5,        0),
    ("one element absent",  [5],            3,       -1),
    ("target is first",    [1, 2, 3, 4, 5], 1,        0),
    ("target is last",     [1, 2, 3, 4, 5], 5,        4),
    ("absent below range", [1, 2, 3],       0,       -1),
    ("absent above range", [1, 2, 3],       9,       -1),
    ("absent in a gap",    [1, 3, 5, 7],    4,       -1),
    ("two elements",       [1, 2],          2,        1),
    ("negatives",          [-5, -3, -1],   -3,        1),
    ("extreme values",     [INT_MIN, 0, INT_MAX], INT_MAX, 2),
    ("extreme low",        [INT_MIN, 0, INT_MAX], INT_MIN, 0),
]


class BinarySearch(unittest.TestCase):
    def test_spec_cases(self):
        for name, nums, target, want in CASES:
            with self.subTest(name):
                self.assertEqual(search(list(nums), target), want)

    def test_result_is_valid(self):
        for name, nums, target, _ in CASES:
            i = search(list(nums), target)
            if i != -1:
                self.assertEqual(nums[i], target, name)

    def test_input_not_modified(self):
        nums = [1, 2, 3, 4, 5]
        search(nums, 3)
        self.assertEqual(nums, [1, 2, 3, 4, 5])

    def test_every_index_findable(self):
        nums = list(range(0, 20000, 2))       # 10,000 elements
        for i, v in enumerate(nums):
            self.assertEqual(search(nums, v), i)

    def test_absent_values_all_return_minus_one(self):
        nums = list(range(0, 20000, 2))
        for v in range(1, 20000, 2):          # every odd value is absent
            self.assertEqual(search(nums, v), -1)

    def test_it_really_is_logarithmic(self):
        # Teaching note 2: 10,000 elements must never take more than
        # ceil(log2(10001)) = 14 iterations.
        nums = list(range(10000))
        limit = math.ceil(math.log2(len(nums) + 1))
        for v in (0, 5000, 9999):
            _, steps = search_counting(nums, v)
            self.assertLessEqual(steps, limit, f"{steps} steps for {v}")

    def test_terminates_on_every_absent_target_in_small_arrays(self):
        # Invariant 2. An infinite loop here would hang the suite, which is the
        # honest way to find out.
        for n in range(0, 12):
            nums = list(range(n))
            for t in range(-2, n + 3):
                search(nums, t)


if __name__ == "__main__":
    unittest.main(verbosity=2)
