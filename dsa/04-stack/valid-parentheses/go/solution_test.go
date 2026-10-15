package validparentheses

import (
	"strings"
	"testing"
)

func TestSpecCases(t *testing.T) {
	cases := []struct {
		name string
		s    string
		want bool
	}{
		{"single opener", "(", false},
		{"single closer", ")", false},
		{"simple", "()", true},
		{"all three types", "()[]{}", true},
		{"nested", "([{}])", true},
		{"interleaved", "([)]", false},
		{"closes too early", ")(", false},
		{"left open", "(((", false},
		{"empty string", "", true},
		{"long balanced", strings.Repeat("(", 5000) + strings.Repeat(")", 5000), true},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			if got := IsValid(c.s); got != c.want {
				t.Errorf("IsValid(%q) = %v, want %v", c.s, got, c.want)
			}
		})
	}
}
