/**
 * linked-list-cycle. Time O(n), Space O(1). Floyd's tortoise and hare.
 *
 * `==` on references is identity. Using .equals on a node would call a method
 * the class may override, which is the wrong question entirely.
 */
public final class Solution {
    private Solution() { }

    public static final class ListNode {
        public int val;
        public ListNode next;
        public ListNode(int val) { this.val = val; }
    }

    public static boolean hasCycle(ListNode head) {
        ListNode slow = head, fast = head;
        while (fast != null && fast.next != null) {   // fast.next safe only if fast non-null
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) return true;            // reference identity
        }
        return false;
    }
}
