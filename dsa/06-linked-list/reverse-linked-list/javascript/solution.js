'use strict';
/**
 * reverse-linked-list. Time O(n), Space O(1).
 *
 * Objects are references, as in Python and Java. The garbage collector owns the
 * nodes. Assignments rebind references and free nothing.
 *
 * @typedef {{ val: number, next: ListNode | null }} ListNode
 * @param {ListNode | null} head
 * @returns {ListNode | null}
 */
function reverseList(head) {
  let prev = null;
  let cur = head;
  while (cur !== null) {
    const nxt = cur.next; // save the rest BEFORE rewriting cur.next
    cur.next = prev;      // flip this link
    prev = cur;           // the reversed part grows by one
    cur = nxt;            // step into the unreversed rest
  }
  return prev;
}

class ListNode {
  constructor(val, next = null) {
    this.val = val;
    this.next = next;
  }
}
module.exports = { reverseList, ListNode };
