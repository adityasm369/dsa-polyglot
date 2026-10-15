"""reverse-linked-list. Time O(n), Space O(1).

Python has no pointers, so `next` is a reference to a ListNode object. Reversing
is rebinding those references. The garbage collector owns the nodes; nothing
here frees anything, and nothing here can leak -- which is the lesson the C
version teaches the hard way.
"""
from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next: "Optional[ListNode]" = None):
        self.val = val
        self.next = next


def reverse_list(head: Optional[ListNode]) -> Optional[ListNode]:
    prev: Optional[ListNode] = None
    cur = head
    while cur is not None:
        nxt = cur.next      # save the rest BEFORE rewriting cur.next
        cur.next = prev     # flip this link
        prev = cur          # the reversed part grows by one
        cur = nxt           # step into the unreversed rest
    return prev
