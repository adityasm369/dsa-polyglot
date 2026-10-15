// Package reverselinkedlist solves reverse-linked-list. Time O(n), Space O(1).
//
// The garbage collector owns every node. This function rewires pointers and
// never frees anything, so there is nothing to leak and nothing to double-free.
// Compare the C version, where the same four lines are correct only because of
// a discipline the compiler cannot check.
package reverselinkedlist

// ListNode is a singly linked list node.
type ListNode struct {
	Val  int
	Next *ListNode
}

// Reverse reverses the list in place and returns the new head.
func Reverse(head *ListNode) *ListNode {
	var prev *ListNode
	for head != nil {
		next := head.Next // save the rest BEFORE rewriting head.Next
		head.Next = prev  // flip this link
		prev = head       // the reversed part grows by one
		head = next       // step into the unreversed rest
	}
	return prev
}
