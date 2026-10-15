"""linked-list-cycle. Time O(n), Space O(1). Floyd's tortoise and hare.

Identity, not equality: `is` compares the node objects. Two nodes can hold the
same value and be different nodes, so `==` on values would report false cycles.
"""
from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: "Optional[ListNode]" = None):
        self.val = val
        self.next = next


def has_cycle(head: Optional[ListNode]) -> bool:
    slow = fast = head
    # Both pointers must be checked: fast.next is only safe when fast is not None.
    while fast is not None and fast.next is not None:
        slow = slow.next
        fast = fast.next.next
        if slow is fast:          # identity: the pointers met inside the cycle
            return True
    return False
