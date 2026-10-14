//! valid-palindrome. Time O(n), Space O(1).
//!
//! **`s[i]` does not compile in Rust.** A `String` is guaranteed UTF-8, and
//! byte `i` may land in the middle of a multi-byte character, so the language
//! refuses the operation rather than returning half a character the way Java,
//! Go and JavaScript do. That refusal is the single best teaching moment in
//! this repository: the other six let you write code that is wrong for any
//! input outside ASCII and say nothing.
//!
//! The honest way to walk from both ends is `.as_bytes()` -- explicitly saying
//! "I am working in bytes, and I know my input is ASCII" -- which is exactly
//! what the spec's constraint licenses. Making that assumption *visible* is the
//! difference between Rust and the rest.

/// True if `s` reads the same both ways over alphanumerics, ignoring case.
/// Takes `&str`: a borrow, so the caller's string cannot be modified or moved.
pub fn is_palindrome(s: &str) -> bool {
    // Deliberate and documented: the spec constrains input to printable ASCII,
    // so one byte is one character. Remove that constraint and this is wrong,
    // which is why it is a cast and not an accident.
    let b = s.as_bytes();
    if b.is_empty() {
        return true;
    }
    let (mut i, mut j) = (0usize, b.len() - 1);
    while i < j {
        // Both skips re-check i < j. Without it, j -= 1 at zero underflows --
        // which in debug Rust PANICS rather than silently wrapping to
        // usize::MAX as C's size_t would. A crash beats a buffer overrun.
        while i < j && !b[i].is_ascii_alphanumeric() {
            i += 1;
        }
        while i < j && !b[j].is_ascii_alphanumeric() {
            j -= 1;
        }
        if !b[i].eq_ignore_ascii_case(&b[j]) {
            return false;
        }
        i += 1;
        j -= 1;
    }
    true
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn spec_cases() {
        for (name, s, want) in [
            ("empty", "", true),
            ("one character", "a", true),
            ("only punctuation", ".,!", true),
            ("mixed case", "Aa", true),
            ("digits count", "0P", false),
            ("the textbook one", "A man, a plan, a canal: Panama", true),
            ("nearly", "race a car", false),
            ("all skipped but one", "...a...", true),
            ("spaces only", "   ", true),
            ("digits palindrome", "12321", true),
            ("digits not", "12345", false),
        ] {
            assert_eq!(is_palindrome(s), want, "{name}");
        }
    }

    #[test]
    fn long_input() {
        assert!(is_palindrome(&"a".repeat(200_000)));
    }

    /// The borrow is the proof of invariant 2: the signature takes `&str`, so
    /// the string is still owned and unchanged afterwards. A mutation would
    /// not compile.
    #[test]
    fn input_is_borrowed() {
        let s = String::from("A man, a plan");
        let _ = is_palindrome(&s);
        assert_eq!(s, "A man, a plan");
    }

    /// Why `s[i]` is not used. This is the line that will not compile:
    ///     let _ = s[0];
    /// error[E0277]: the type `str` cannot be indexed by `{integer}`
    /// Documented as a test so a student reads it rather than wondering.
    #[test]
    fn strings_cannot_be_indexed() {
        let s = "héllo";
        assert_eq!(s.len(), 6);            // SIX bytes
        assert_eq!(s.chars().count(), 5);  // FIVE characters
        // Java, Go and JavaScript would hand you byte 1 and call it a character.
    }
}
