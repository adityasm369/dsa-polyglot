//! binary-search. Time O(log n), Space O(1).
//!
//! Rust is the only language in this repository that tells you about the
//! overflow **at runtime, by default**: in a debug build `lo + hi` panics with
//! "attempt to add with overflow". In release it wraps silently, like Java.
//! Run `make test` then `make release` and watch the same code behave
//! differently -- that is the honest one-line summary of this whole comparison.

/// Index of `target` in the ascending, duplicate-free `nums`, or `None`.
/// Takes `&[i32]`: a borrow, so the input cannot be modified.
pub fn search(nums: &[i32], target: i32) -> Option<usize> {
    if nums.is_empty() {
        return None;
    }
    let (mut lo, mut hi) = (0usize, nums.len() - 1);
    loop {
        // lo + (hi - lo) / 2. With usize there is no negative to fall back on,
        // so each branch checks the boundary BEFORE stepping -- mid - 1 at zero
        // would underflow, and in debug Rust that is a panic, not a wrap.
        let mid = lo + (hi - lo) / 2;
        if nums[mid] == target {
            return Some(mid);
        }
        if nums[mid] < target {
            if mid == hi {
                return None;
            }
            lo = mid + 1;
        } else {
            if mid == lo {
                return None;
            }
            hi = mid - 1;
        }
    }
}

/// Same, returning the iteration count for the O(log n) teaching note.
pub fn search_counting(nums: &[i32], target: i32) -> (Option<usize>, u32) {
    let mut steps = 0;
    if nums.is_empty() {
        return (None, 0);
    }
    let (mut lo, mut hi) = (0usize, nums.len() - 1);
    loop {
        steps += 1;
        let mid = lo + (hi - lo) / 2;
        if nums[mid] == target {
            return (Some(mid), steps);
        }
        if nums[mid] < target {
            if mid == hi { return (None, steps); }
            lo = mid + 1;
        } else {
            if mid == lo { return (None, steps); }
            hi = mid - 1;
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn spec_cases() {
        let ext = [i32::MIN, 0, i32::MAX];
        for (name, nums, target, want) in [
            ("empty array", &[][..], 5, None),
            ("one element present", &[5][..], 5, Some(0)),
            ("one element absent", &[5][..], 3, None),
            ("target is first", &[1, 2, 3, 4, 5][..], 1, Some(0)),
            ("target is last", &[1, 2, 3, 4, 5][..], 5, Some(4)),
            ("absent below range", &[1, 2, 3][..], 0, None),
            ("absent above range", &[1, 2, 3][..], 9, None),
            ("absent in a gap", &[1, 3, 5, 7][..], 4, None),
            ("two elements", &[1, 2][..], 2, Some(1)),
            ("negatives", &[-5, -3, -1][..], -3, Some(1)),
            ("extreme values", &ext[..], i32::MAX, Some(2)),
            ("extreme low", &ext[..], i32::MIN, Some(0)),
        ] {
            assert_eq!(search(nums, target), want, "{name}");
        }
    }

    #[test]
    fn every_index_findable() {
        let nums: Vec<i32> = (0..10_000).map(|i| i * 2).collect();
        for (i, &v) in nums.iter().enumerate() {
            assert_eq!(search(&nums, v), Some(i));
            assert_eq!(search(&nums, v + 1), None);
        }
    }

    #[test]
    fn is_logarithmic() {
        let nums: Vec<i32> = (0..10_000).collect();
        let limit = (nums.len() as f64 + 1.0).log2().ceil() as u32;
        for v in [0, 5_000, 9_999] {
            let (_, steps) = search_counting(&nums, v);
            assert!(steps <= limit, "{steps} steps, limit {limit}");
        }
    }

    /// Invariant 2. An infinite loop here hangs the suite, which is honest.
    #[test]
    fn terminates_everywhere() {
        for n in 0..12i32 {
            let nums: Vec<i32> = (0..n).collect();
            for t in -2..n + 3 {
                let _ = search(&nums, t);
            }
        }
    }

    /// The bug itself, demonstrated rather than described. On a 32-bit index
    /// type, lo + hi overflows where lo + (hi - lo) / 2 does not.
    #[test]
    fn the_jdk_bug() {
        let (lo, hi): (i32, i32) = (1 << 30, (1 << 30) + 2);
        assert_eq!(lo.checked_add(hi), None, "lo + hi overflows i32");
        assert_eq!(lo + (hi - lo) / 2, 1_073_741_825, "the safe form does not");
    }
}
