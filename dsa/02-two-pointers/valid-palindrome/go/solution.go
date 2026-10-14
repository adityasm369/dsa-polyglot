// Package validpalindrome solves valid-palindrome. Time O(n), Space O(1).
//
// Go's string is immutable bytes. s[i] is a BYTE, not a character -- for the
// ASCII this spec allows that is the same thing, and for anything else it is
// not. `for i, r := range s` decodes UTF-8 into runes, which is the correct
// general form, but it only walks forwards and this algorithm needs to walk
// from both ends. Converting to []rune would make it correct for Unicode and
// cost O(n) space, breaking the invariant. That trade is worth naming.
package validpalindrome

// IsPalindrome reports whether s reads the same both ways over alphanumerics,
// ignoring case. s is immutable, so invariant 2 holds by construction.
func IsPalindrome(s string) bool {
	if len(s) == 0 {
		return true
	}
	alnum := func(c byte) bool {
		return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
	}
	lower := func(c byte) byte {
		if c >= 'A' && c <= 'Z' {
			return c + 32
		}
		return c
	}
	i, j := 0, len(s)-1
	for i < j {
		// Both skips re-check i < j: ".,!" would otherwise index past the end
		// and panic with a runtime slice-bounds error.
		for i < j && !alnum(s[i]) {
			i++
		}
		for i < j && !alnum(s[j]) {
			j--
		}
		if lower(s[i]) != lower(s[j]) {
			return false
		}
		i++
		j--
	}
	return true
}
