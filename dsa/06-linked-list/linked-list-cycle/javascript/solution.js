'use strict';
/**
 * linked-list-cycle. Time O(n), Space O(1). Floyd's tortoise and hare.
 *
 * `===` on objects is identity, as in Java's `==`. Two distinct nodes holding
 * the same value are unequal, which is the property the spec's "equal values"
 * case checks. Do not compare the .val fields.
 *
 * @param {{ val: number, next: any } | null} head
 * @returns {boolean}
 */
function hasCycle(head) {
  let slow = head, fast = head;
  while (fast !== null && fast.next !== null) {  // fast.next safe only if fast non-null
    slow = slow.next;
    fast = fast.next.next;
    if (slow === fast) return true;              // identity
  }
  return false;
}
module.exports = { hasCycle };
