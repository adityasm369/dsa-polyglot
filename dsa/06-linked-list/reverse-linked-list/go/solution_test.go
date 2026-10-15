package reverselinkedlist

import (
	"slices"
	"testing"
)

func build(values []int) *ListNode {
	var head *ListNode
	for i := len(values) - 1; i >= 0; i-- {
		head = &ListNode{Val: values[i], Next: head}
	}
	return head
}

func collect(head *ListNode) []int {
	var out []int
	for ; head != nil; head = head.Next {
		out = append(out, head.Val)
	}
	return out
}

func TestSpecCases(t *testing.T) {
	cases := []struct {
		name   string
		values []int
		want   []int
	}{
		{"empty", nil, nil},
		{"one node", []int{1}, []int{1}},
		{"two nodes", []int{1, 2}, []int{2, 1}},
		{"odd length", []int{1, 2, 3}, []int{3, 2, 1}},
		{"negatives and zero", []int{-1, 0, 1}, []int{1, 0, -1}},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			if got := collect(Reverse(build(c.values))); !slices.Equal(got, c.want) {
				t.Errorf("got %v, want %v", got, c.want)
			}
		})
	}
}

// Invariant 2: the original head is now the tail.
func TestOriginalHeadIsNowTail(t *testing.T) {
	head := build([]int{1, 2, 3})
	Reverse(head)
	if head.Next != nil {
		t.Error("old head still points at a node")
	}
}

func TestReverseTwiceIsIdentity(t *testing.T) {
	values := []int{4, 1, 3, 2}
	if got := collect(Reverse(Reverse(build(values)))); !slices.Equal(got, values) {
		t.Errorf("got %v, want %v", got, values)
	}
}

// 100,000 nodes. Go's goroutine stacks grow, so a recursive version would pass
// here -- the test is kept so every language is held to the same standard.
func TestLongList(t *testing.T) {
	values := make([]int, 100000)
	for i := range values {
		values[i] = i
	}
	got := collect(Reverse(build(values)))
	if len(got) != 100000 || got[0] != 99999 {
		t.Errorf("long list reversed wrongly: len %d", len(got))
	}
}
