// Package linkedlistcycle solves linked-list-cycle. Time O(n), Space O(1).
//
// Floyd's tortoise and hare. Comparing *ListNode values compares pointers, which
// is node identity -- the question asked. Comparing the Val fields would report
// a cycle between any two nodes that happen to hold the same number.
package linkedlistcycle

// ListNode is a singly linked list node.
type ListNode struct {
	Val  int
	Next *ListNode
}

// HasCycle reports whether following Next from head revisits a node.
func HasCycle(head *ListNode) bool {
	slow, fast := head, head
	for fast != nil && fast.Next != nil { // fast.Next is safe only if fast is non-nil
		slow = slow.Next
		fast = fast.Next.Next
		if slow == fast { // pointer identity: the gap closed inside the cycle
			return true
		}
	}
	return false
}
