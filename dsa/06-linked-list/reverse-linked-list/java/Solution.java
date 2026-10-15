/**
 * reverse-linked-list. Time O(n), Space O(1).
 *
 * The garbage collector owns every node. reverse() rewires references and
 * frees nothing, and it cannot leak, because nothing here is ever manually
 * released. The cost is that nothing tells you when a node is freed either.
 */
public final class Solution {
    private Solution() { }

    public static final class ListNode {
        public int val;
        public ListNode next;
        public ListNode(int val, ListNode next) { this.val = val; this.next = next; }
    }

    public static ListNode reverse(ListNode head) {
        ListNode prev = null;
        while (head != null) {
            ListNode next = head.next; // save the rest BEFORE rewriting
            head.next = prev;          // flip this link
            prev = head;               // the reversed part grows by one
            head = next;               // step into the unreversed rest
        }
        return prev;
    }
}
