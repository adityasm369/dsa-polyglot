//! reverse-linked-list. Time O(n), Space O(1).
//!
//! Ownership is the whole problem, and Rust makes it visible. Each node is
//! owned by exactly one `Option<Box<ListNode>>`. To move a node you must
//! `take()` it out of its owner, which replaces the owner with `None` -- so
//! there is never a moment where two live references point at the same node.
//! The naive C reversal creates exactly that moment, and then has to get the
//! order of pointer writes right to survive it.

#[derive(Debug, PartialEq, Eq)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

/// Takes ownership of the list and returns the reversed one. The signature is
/// the proof: the caller cannot keep using the original head afterwards.
pub fn reverse_list(mut head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
    let mut prev: Option<Box<ListNode>> = None;
    while let Some(mut node) = head {
        // take() moves the rest of the list out of `node` and leaves None behind.
        // That is the "save next before rewriting" step, expressed as a move
        // the compiler checks, rather than a discipline it does not.
        head = node.next.take();
        node.next = prev;
        prev = Some(node);
    }
    prev
}

#[cfg(test)]
mod tests {
    use super::*;

    fn build(values: &[i32]) -> Option<Box<ListNode>> {
        let mut head = None;
        for &v in values.iter().rev() {
            head = Some(Box::new(ListNode { val: v, next: head }));
        }
        head
    }

    fn collect(head: &Option<Box<ListNode>>) -> Vec<i32> {
        let mut out = Vec::new();
        let mut cur = head;
        while let Some(node) = cur {
            out.push(node.val);
            cur = &node.next;
        }
        out
    }

    #[test]
    fn spec_cases() {
        for (name, values, want) in [
            ("empty", vec![], vec![]),
            ("one node", vec![1], vec![1]),
            ("two nodes", vec![1, 2], vec![2, 1]),
            ("odd length", vec![1, 2, 3], vec![3, 2, 1]),
            ("negatives and zero", vec![-1, 0, 1], vec![1, 0, -1]),
        ] {
            assert_eq!(collect(&reverse_list(build(&values))), want, "{name}");
        }
    }

    #[test]
    fn reverse_twice_is_identity() {
        let v = vec![4, 1, 3, 2];
        assert_eq!(collect(&reverse_list(reverse_list(build(&v)))), v);
    }

    /// Invariant 1, asserted by the type system: the input was moved in, so no
    /// node can be lost or duplicated by a reference the caller still holds.
    /// The following line would not compile:
    ///     let r = reverse_list(head); let _ = head; // error: use of moved value
    #[test]
    fn input_is_consumed() {
        let head = build(&[1, 2, 3]);
        let r = reverse_list(head);
        assert_eq!(collect(&r), vec![3, 2, 1]);
    }

    /// 100,000 nodes. Dropping a long Box chain is itself recursive in Rust's
    /// default Drop, so a list this long can overflow on DROP even when the
    /// reversal is iterative. The test keeps the list small enough to drop
    /// safely and documents the trap; the C and Java versions show the same
    /// class of problem from the other side.
    #[test]
    fn long_list_reverses() {
        let values: Vec<i32> = (0..10_000).collect();
        let r = reverse_list(build(&values));
        assert_eq!(r.as_ref().map(|n| n.val), Some(9_999));
    }
}
