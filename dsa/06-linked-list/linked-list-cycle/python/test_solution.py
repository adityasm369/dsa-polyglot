import unittest
from solution import ListNode, has_cycle


def build(values):
    head = None
    for v in reversed(values):
        head = ListNode(v, head)
    return head


def nodes_of(head):
    out = []
    while head is not None:
        out.append(head)
        head = head.next
    return out


class LinkedListCycle(unittest.TestCase):
    def test_empty(self):
        self.assertFalse(has_cycle(None))

    def test_one_node_no_cycle(self):
        self.assertFalse(has_cycle(build([1])))

    def test_two_nodes_no_cycle(self):
        self.assertFalse(has_cycle(build([1, 2])))

    def test_one_node_points_at_itself(self):
        n = ListNode(1)
        n.next = n
        self.assertTrue(has_cycle(n))

    def test_cycle_back_to_head(self):
        ns = nodes_of(build([1, 2, 3]))
        ns[-1].next = ns[0]
        self.assertTrue(has_cycle(ns[0]))

    def test_cycle_to_middle(self):
        ns = nodes_of(build([1, 2, 3, 4]))
        ns[-1].next = ns[1]
        self.assertTrue(has_cycle(ns[0]))

    def test_identity_not_value(self):
        # Equal VALUES, distinct nodes, no cycle: must be false.
        self.assertFalse(has_cycle(build([7, 7, 7, 7])))

    def test_long_no_cycle(self):
        self.assertFalse(has_cycle(build(list(range(10000)))))

    def test_long_cycle_at_end(self):
        ns = nodes_of(build(list(range(10000))))
        ns[-1].next = ns[0]
        self.assertTrue(has_cycle(ns[0]))

    def test_does_not_modify_list(self):
        ns = nodes_of(build([1, 2, 3]))
        ns[-1].next = ns[1]
        has_cycle(ns[0])
        self.assertIs(ns[-1].next, ns[1])
        self.assertEqual([n.val for n in ns], [1, 2, 3])


if __name__ == "__main__":
    unittest.main(verbosity=2)
