//! linked-list-cycle. Time O(n), Space O(1). Floyd's tortoise and hare.
//!
//! Rust's `Option<Box<Node>>` owns its successor, so a safe list **cannot form
//! a cycle at all**: ownership is a tree, and a cycle would need two owners.
//! Rust therefore has no safe way to build the input this problem is about. The
//! function below takes a *graph* instead, as indices into a slice -- the arena
//! pattern real Rust code uses for linked structures. That is an honest
//! limitation of the language, shown rather than hidden.

/// `next[i]` is the index of node i's successor, or `None` at the end.
/// Takes `&[Option<usize>]`: a borrow, so the structure is not modified.
pub fn has_cycle(next: &[Option<usize>], head: Option<usize>) -> bool {
    let mut slow = head;
    let mut fast = head;
    loop {
        // fast must exist AND have a successor before stepping two.
        let Some(f) = fast else { return false };
        let Some(f1) = next[f] else { return false };
        fast = next[f1];
        slow = slow.and_then(|s| next[s]);
        if slow.is_some() && slow == fast {
            return true;
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Builds the arena: node i points at next[i]. `tail_to` closes a loop.
    fn chain(n: usize, tail_to: Option<usize>) -> Vec<Option<usize>> {
        let mut v: Vec<Option<usize>> = (0..n).map(|i| if i + 1 < n { Some(i + 1) } else { None }).collect();
        if let (Some(t), Some(last)) = (tail_to, v.len().checked_sub(1)) {
            v[last] = Some(t);
        }
        v
    }

    #[test]
    fn empty() {
        assert!(!has_cycle(&[], None));
    }

    #[test]
    fn one_and_two_nodes_no_cycle() {
        assert!(!has_cycle(&chain(1, None), Some(0)));
        assert!(!has_cycle(&chain(2, None), Some(0)));
    }

    #[test]
    fn one_node_self_loop() {
        assert!(has_cycle(&[Some(0)], Some(0)));
    }

    #[test]
    fn cycle_back_to_head() {
        assert!(has_cycle(&chain(3, Some(0)), Some(0)));
    }

    #[test]
    fn cycle_to_middle() {
        assert!(has_cycle(&chain(4, Some(1)), Some(0)));
    }

    #[test]
    fn long_both_shapes() {
        assert!(!has_cycle(&chain(10_000, None), Some(0)));
        assert!(has_cycle(&chain(10_000, Some(0)), Some(0)));
    }

    /// The input slice is borrowed, not consumed: the caller can ask again.
    #[test]
    fn does_not_modify() {
        let g = chain(3, Some(1));
        let before = g.clone();
        let _ = has_cycle(&g, Some(0));
        assert_eq!(g, before);
    }
}
