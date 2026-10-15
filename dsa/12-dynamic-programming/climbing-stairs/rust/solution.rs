//! climbing-stairs. Time O(n), Space O(1).
//!
//! `u64` for the accumulator. In debug builds the addition panics on overflow
//! rather than wrapping, so an out-of-range n fails loudly during testing.

pub fn climb_stairs(n: u32) -> u64 {
    if n <= 2 {
        return u64::from(n);       // ways(0) is treated as 0, ways(1)=1, ways(2)=2
    }
    let (mut prev, mut cur) = (1u64, 2u64);
    for _ in 3..=n {
        let next = prev + cur;     // the last move was a 1 or a 2; debug-checked
        prev = cur;
        cur = next;
    }
    cur
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn spec_cases() {
        for (n, want) in [(1, 1), (2, 2), (3, 3), (4, 5), (5, 8), (10, 89), (45, 1_836_311_903)] {
            assert_eq!(climb_stairs(n), want, "n={n}");
        }
    }

    #[test]
    fn every_answer_positive() {
        for n in 1..=45 {
            assert!(climb_stairs(n) > 0);
        }
    }

    /// Past n = 92 the u64 overflows. In debug this panics; that is the test.
    #[test]
    #[should_panic(expected = "overflow")]
    fn overflow_is_loud_in_debug() {
        let _ = climb_stairs(100);
    }
}
