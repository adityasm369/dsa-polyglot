//! valid-parentheses. Time O(n), Space O(n).
//!
//! `Vec` is the stack. `pop()` returns `Option<T>`, so the empty case cannot be
//! ignored: the compiler makes you write the `None` arm. Compare C, where
//! popping an empty stack is a silent read of whatever sits below the array.

pub fn is_valid(s: &str) -> bool {
    let mut stack: Vec<char> = Vec::with_capacity(s.len() / 2 + 1);
    for c in s.chars() {
        match c {
            '(' | '[' | '{' => stack.push(c),
            ')' | ']' | '}' => {
                let want = match c {
                    ')' => '(',
                    ']' => '[',
                    _ => '{',
                };
                // `?`-style early exit: no opener means invalid.
                match stack.pop() {
                    Some(open) if open == want => {}
                    _ => return false,
                }
            }
            _ => return false, // outside the spec
        }
    }
    stack.is_empty()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn spec_cases() {
        for (name, s, want) in [
            ("single opener", "(", false),
            ("single closer", ")", false),
            ("simple", "()", true),
            ("all three types", "()[]{}", true),
            ("nested", "([{}])", true),
            ("interleaved", "([)]", false),
            ("closes too early", ")(", false),
            ("left open", "(((", false),
            ("empty string", "", true),
        ] {
            assert_eq!(is_valid(s), want, "{name}");
        }
    }

    #[test]
    fn long_balanced() {
        let s = "(".repeat(5000) + &")".repeat(5000);
        assert!(is_valid(&s));
    }
}
