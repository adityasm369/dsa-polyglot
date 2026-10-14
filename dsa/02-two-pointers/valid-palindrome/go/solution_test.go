package validpalindrome

import "testing"

func TestSpecCases(t *testing.T) {
	cases := []struct {
		name string
		s    string
		want bool
	}{
		{"empty", "", true},
		{"one character", "a", true},
		{"only punctuation", ".,!", true},
		{"mixed case", "Aa", true},
		{"digits count", "0P", false},
		{"the textbook one", "A man, a plan, a canal: Panama", true},
		{"nearly", "race a car", false},
		{"all skipped but one", "...a...", true},
		{"spaces only", "   ", true},
		{"digits palindrome", "12321", true},
		{"digits not", "12345", false},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			if got := IsPalindrome(c.s); got != c.want {
				t.Errorf("IsPalindrome(%q) = %v, want %v", c.s, got, c.want)
			}
		})
	}
}

func TestLongInput(t *testing.T) {
	big := make([]byte, 200000)
	for i := range big {
		big[i] = 'a'
	}
	if !IsPalindrome(string(big)) {
		t.Error("200k identical characters should be a palindrome")
	}
}

// Documents the byte-vs-rune limitation rather than hiding it: this input is
// outside the spec's ASCII constraint, and the byte-based comparison handles
// it only because UTF-8 is symmetric for a two-byte sequence read backwards
// when the characters are identical. It is NOT general.
func TestNonASCIIIsOutsideTheSpec(t *testing.T) {
	if !IsPalindrome("é") {
		t.Log("single non-ASCII char: bytes are skipped as non-alnum, so vacuously true")
	}
}

func BenchmarkIsPalindrome(b *testing.B) {
	s := "A man, a plan, a canal: Panama"
	for n := 0; n < b.N; n++ {
		IsPalindrome(s)
	}
}
