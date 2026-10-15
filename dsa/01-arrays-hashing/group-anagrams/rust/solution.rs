//! group-anagrams. Time O(n*k), Space O(n*k).
//!
//! The key is `[u8; 26]`. Rust arrays implement `Hash` and `Eq` by value, so
//! this works directly as a `HashMap` key -- no encoding into a string, and no
//! hand-written hash. Compare Java, where an `int[]` key silently fails because
//! arrays there hash by identity, and C++, where `std::array` has `operator<`
//! for `std::map` but no `std::hash` for `std::unordered_map`.
//!
//! `u8` is sound only because the spec caps string length at 100, so no count
//! can exceed 255. A `debug_assert!` records that dependency rather than
//! leaving it to a comment.

use std::collections::HashMap;

pub fn group_anagrams(strs: &[String]) -> Vec<Vec<String>> {
    let mut index: HashMap<[u8; 26], usize> = HashMap::new();
    let mut out: Vec<Vec<String>> = Vec::new();

    for s in strs {
        debug_assert!(s.len() <= 255, "a count would overflow u8");
        let mut counts = [0u8; 26];
        for b in s.bytes() {
            if b.is_ascii_lowercase() {
                counts[(b - b'a') as usize] += 1;
            }
        }
        match index.get(&counts) {
            Some(&g) => out[g].push(s.clone()),
            None => {
                index.insert(counts, out.len());
                out.push(vec![s.clone()]);
            }
        }
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    fn is_anagram(a: &str, b: &str) -> bool {
        let mut x: Vec<char> = a.chars().collect();
        let mut y: Vec<char> = b.chars().collect();
        x.sort_unstable();
        y.sort_unstable();
        x == y
    }

    fn check_partition(strs: &[&str], want_groups: usize) {
        let owned: Vec<String> = strs.iter().map(|s| s.to_string()).collect();
        let groups = group_anagrams(&owned);
        assert_eq!(groups.len(), want_groups, "group count for {strs:?}");

        // Invariant 1: every string appears exactly once.
        let mut flat: Vec<String> = groups.iter().flatten().cloned().collect();
        let mut want = owned.clone();
        flat.sort();
        want.sort();
        assert_eq!(flat, want, "strings lost or duplicated");

        // Invariant 2, both directions.
        for (gi, g) in groups.iter().enumerate() {
            for a in g {
                for b in g {
                    assert!(is_anagram(a, b), "{a}/{b} merged wrongly");
                }
                for (gj, h) in groups.iter().enumerate() {
                    if gi == gj {
                        continue;
                    }
                    for b in h {
                        assert!(!is_anagram(a, b), "{a}/{b} split wrongly");
                    }
                }
            }
        }
    }

    #[test]
    fn spec_cases() {
        check_partition(&["a"], 1);
        check_partition(&[""], 1);
        check_partition(&["", ""], 1);
        check_partition(&["abc", "def"], 2);
        check_partition(&["eat", "tea", "tan", "ate", "nat", "bat"], 3);
        check_partition(&["aab", "abb"], 2);
        check_partition(&["ab", "ab"], 1);
        check_partition(&["eat", "tea", "tan", "ate", "nat", "bat", "", "aab"], 5);
    }

    #[test]
    fn empty_input() {
        let none: Vec<String> = Vec::new();
        assert!(group_anagrams(&none).is_empty());
    }

    /// Arrays hash by value in Rust -- the thing Java's int[] cannot do.
    #[test]
    fn array_keys_hash_by_value() {
        let mut m: HashMap<[u8; 2], &str> = HashMap::new();
        m.insert([1, 2], "x");
        assert_eq!(m.get(&[1, 2]), Some(&"x"));
    }
}
