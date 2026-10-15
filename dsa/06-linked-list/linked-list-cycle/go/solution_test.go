package linkedlistcycle

import "testing"

func build(values ...int) []*ListNode {
	ns := make([]*ListNode, len(values))
	for i, v := range values {
		ns[i] = &ListNode{Val: v}
	}
	for i := 0; i+1 < len(ns); i++ {
		ns[i].Next = ns[i+1]
	}
	return ns
}

func TestSpecCases(t *testing.T) {
	cases := []struct {
		name string
		head func() *ListNode
		want bool
	}{
		{"empty", func() *ListNode { return nil }, false},
		{"one node, no cycle", func() *ListNode { return build(1)[0] }, false},
		{"two nodes, no cycle", func() *ListNode { return build(1, 2)[0] }, false},
		{"one node, self-loop", func() *ListNode {
			n := build(1)[0]
			n.Next = n
			return n
		}, true},
		{"cycle back to head", func() *ListNode {
			ns := build(1, 2, 3)
			ns[2].Next = ns[0]
			return ns[0]
		}, true},
		{"cycle to middle", func() *ListNode {
			ns := build(1, 2, 3, 4)
			ns[3].Next = ns[1]
			return ns[0]
		}, true},
		{"equal values, no cycle", func() *ListNode { return build(7, 7, 7, 7)[0] }, false},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			if got := HasCycle(c.head()); got != c.want {
				t.Errorf("got %v, want %v", got, c.want)
			}
		})
	}
}

func TestLong(t *testing.T) {
	v := make([]int, 10000)
	for i := range v {
		v[i] = i
	}
	ns := build(v...)
	if HasCycle(ns[0]) {
		t.Error("long list without a cycle reported one")
	}
	ns[len(ns)-1].Next = ns[0]
	if !HasCycle(ns[0]) {
		t.Error("long list with a cycle at the end was missed")
	}
}
