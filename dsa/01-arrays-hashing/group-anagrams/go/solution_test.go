package groupanagrams

import (
	"reflect"
	"sort"
	"testing"
)

// normal returns the groups in a canonical order, so comparison ignores order.
func normal(groups [][]string) [][]string {
	out := make([][]string, len(groups))
	for i, g := range groups {
		c := append([]string(nil), g...)
		sort.Strings(c)
		out[i] = c
	}
	sort.Slice(out, func(i, j int) bool {
		return join(out[i]) < join(out[j])
	})
	return out
}

func join(g []string) string {
	s := ""
	for _, x := range g {
		s += x + "\x00"
	}
	return s
}

func TestSpecCases(t *testing.T) {
	cases := []struct {
		strs []string
		want [][]string
	}{
		{[]string{"a"}, [][]string{{"a"}}},
		{[]string{""}, [][]string{{""}}},
		{[]string{"", ""}, [][]string{{"", ""}}},
		{[]string{"abc", "def"}, [][]string{{"abc"}, {"def"}}},
		{[]string{"eat", "tea", "tan", "ate", "nat", "bat"},
			[][]string{{"eat", "tea", "ate"}, {"tan", "nat"}, {"bat"}}},
		{[]string{"aab", "abb"}, [][]string{{"aab"}, {"abb"}}},
		{[]string{"ab", "ab"}, [][]string{{"ab", "ab"}}},
	}
	for _, c := range cases {
		if got := GroupAnagrams(c.strs); !reflect.DeepEqual(normal(got), normal(c.want)) {
			t.Errorf("GroupAnagrams(%q) = %q, want %q", c.strs, got, c.want)
		}
	}
}

func TestEveryStringInOneGroup(t *testing.T) {
	strs := []string{"eat", "tea", "tan", "ate", "nat", "bat", "", "aab"}
	var all []string
	for _, g := range GroupAnagrams(strs) {
		all = append(all, g...)
	}
	sort.Strings(all)
	want := append([]string(nil), strs...)
	sort.Strings(want)
	if !reflect.DeepEqual(all, want) {
		t.Errorf("strings lost or duplicated: %q", all)
	}
}
