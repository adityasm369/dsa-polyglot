//! two-sum. Time O(n) average, Space O(n).
//!
//! Three things Rust makes visible that the other six hide:
//!
//! 1. `Option<(usize, usize)>` is not a convention, it is the type. There is no
//!    null to forget, and the caller cannot read the indices without handling
//!    the "no pair" case -- the compiler refuses.
//! 2. `&[i32]` is a borrow. The function *cannot* modify the caller's array;
//!    invariant 3 of SPEC.md is proven by the signature, not by a test.
//! 3. Integer overflow is not silent. In debug builds `a - b` panics on
//!    overflow; in release it wraps. Either is a decision, which is why the
//!    arithmetic here is widened to i64 on purpose rather than by luck.

use std::collections::HashMap;

/// Returns `(i, j)` with `i < j` and `nums[i] + nums[j] == target`,
/// or `None` if no such pair exists.
pub fn two_sum(nums: &[i32], target: i64) -> Option<(usize, usize)> {
    if nums.len() < 2 {
        return None;
    }
    // value -> first index it was seen at
    let mut seen: HashMap<i64, usize> = HashMap::with_capacity(nums.len());
    for (j, &x) in nums.iter().enumerate() {
        // i64: nums values reach 1e9 and target reaches 2e9, so this
        // subtraction would overflow i32. In debug that is a panic, not a wrong
        // answer -- which is the point.
        let want = target - i64::from(x);
        if let Some(&i) = seen.get(&want) {
            return Some((i, j)); // i was inserted earlier, so i < j
        }
        // or_insert keeps the FIRST index on a duplicate, so [3,3] -> (0,1).
        seen.entry(i64::from(x)).or_insert(j);
    }
    None
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Cases from SPEC.md, with the invariants checked for every one.
    fn expect(name: &str, nums: &[i32], target: i64, want: (usize, usize)) {
        let got = two_sum(nums, target)
            .unwrap_or_else(|| panic!("{name}: expected a pair, got None"));
        assert_eq!(got, want, "{name}");
        assert!(got.0 < got.1, "{name}: indices not ordered");
        assert_eq!(
            i64::from(nums[got.0]) + i64::from(nums[got.1]),
            target,
            "{name}: pair does not sum to target"
        );
    }

    #[test]
    fn spec_cases() {
        expect("minimum size", &[1, 2], 3, (0, 1));
        expect("answer at the ends", &[3, 2, 4, 1], 4, (0, 3));
        expect("duplicate values", &[3, 3], 6, (0, 1));
        expect("same value, one pair", &[3, 2, 3], 6, (0, 2));
        expect("negatives", &[-1, -2, -3, -4], -6, (1, 3));
        expect("zero target and zeros", &[0, 0], 0, (0, 1));
        expect("overflow guard", &[1_000_000_000, 1_000_000_000], 2_000_000_000, (0, 1));
        expect("answer in the middle", &[1, 5, 2, 7, 3], 9, (2, 3));
    }

    #[test]
    fn no_pair_is_none() {
        assert_eq!(two_sum(&[1, 2, 3], 100), None);
    }

    #[test]
    fn too_short_is_none() {
        assert_eq!(two_sum(&[], 1), None);
        assert_eq!(two_sum(&[1], 1), None);
    }

    /// The borrow checker proves invariant 3, but the test documents it: the
    /// signature takes `&[i32]`, so a mutation would not compile.
    #[test]
    fn input_is_borrowed_not_moved() {
        let nums = vec![3, 2, 4, 1];
        let _ = two_sum(&nums, 4);
        assert_eq!(nums, vec![3, 2, 4, 1]); // still usable, still unchanged
    }

    /// Widening to i64 is not decoration. At i32 this subtraction overflows,
    /// which panics in debug -- shown here with checked arithmetic.
    #[test]
    fn i32_would_overflow() {
        let target_i32: i32 = 2_000_000_000;
        assert_eq!(target_i32.checked_sub(-2_000_000_000), None, "i32 overflows");
        assert_eq!(i64::from(target_i32) - (-2_000_000_000i64), 4_000_000_000i64);
    }

    #[test]
    fn many_keys() {
        let big: Vec<i32> = (0..2000).collect();
        assert_eq!(two_sum(&big, 1999 + 1998), Some((1998, 1999)));
    }
}
