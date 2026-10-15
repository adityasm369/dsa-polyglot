"""Cases from SPEC.md. python3 -m unittest -v"""
import sys
import unittest
from solution import ListNode, reverse_list


def build(values):
    head = None
    for v in reversed(values):
        head = ListNode(v, head)
    return head


def collect(head):
    out = []
    while head is not None:
        out.append(head.val)
        head = head.next
    return out


class ReverseLinkedList(unittest.TestCase):
    def test_spec_cases(self):
        for name, values, want in [
            ("empty", [], []),
            ("one node", [1], [1]),
            ("two nodes", [1, 2], [2, 1]),
            ("odd length", [1, 2, 3], [3, 2, 1]),
            ("negatives and zero", [-1, 0, 1], [1, 0, -1]),
        ]:
            with self.subTest(name):
                self.assertEqual(collect(reverse_list(build(values))), want)

    def test_original_head_is_now_the_tail(self):
        # Invariant 2: the old head must terminate the list.
        head = build([1, 2, 3])
        reverse_list(head)
        self.assertIsNone(head.next)

    def test_reverse_twice_is_identity(self):
        values = [4, 1, 3, 2]
        self.assertEqual(collect(reverse_list(reverse_list(build(values)))), values)

    def test_every_node_survives(self):
        # Invariant 1: count before and after.
        head = build(list(range(1000)))
        self.assertEqual(len(collect(reverse_list(head))), 1000)

    def test_long_list_does_not_recurse(self):
        # 100,000 nodes. A recursive version raises RecursionError at the
        # default limit of 1000 -- which is why this test exists.
        self.assertGreater(100000, sys.getrecursionlimit())
        head = build(list(range(100000)))
        self.assertEqual(collect(reverse_list(head))[0], 99999)


if __name__ == "__main__":
    unittest.main(verbosity=2)
