import time
import unittest
from solution import climb_stairs, climb_naive

CASES = [(1, 1), (2, 2), (3, 3), (4, 5), (5, 8), (10, 89), (45, 1836311903)]


class ClimbingStairs(unittest.TestCase):
    def test_spec_cases(self):
        for n, want in CASES:
            with self.subTest(n=n):
                self.assertEqual(climb_stairs(n), want)

    def test_every_answer_is_positive(self):
        # Invariant 2: no valid n may return 0.
        self.assertTrue(all(climb_stairs(n) > 0 for n in range(1, 46)))

    def test_naive_agrees_where_naive_finishes(self):
        for n in range(1, 21):
            self.assertEqual(climb_stairs(n), climb_naive(n))

    def test_the_ladder_is_real(self):
        # The point of the pattern: the naive version is measurably slower.
        start = time.perf_counter(); climb_naive(25); slow = time.perf_counter() - start
        start = time.perf_counter(); climb_stairs(25); fast = time.perf_counter() - start
        self.assertLess(fast, slow)


if __name__ == "__main__":
    unittest.main(verbosity=2)
