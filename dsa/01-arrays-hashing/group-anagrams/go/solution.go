// Package groupanagrams solves group-anagrams. Time O(n*k), Space O(n*k).
//
// The map key is a [26]int of letter counts. Arrays are comparable and hashable
// in Go, so the key is a value: two anagrams build equal keys. A []int would not
// compile as a map key, because slices are not comparable.
package groupanagrams

// GroupAnagrams partitions strs into groups of mutual anagrams.
func GroupAnagrams(strs []string) [][]string {
	index := make(map[[26]int]int) // key -> position in out
	var out [][]string
	for _, s := range strs {
		var key [26]int
		for i := 0; i < len(s); i++ {
			key[s[i]-'a']++
		}
		if g, ok := index[key]; ok {
			out[g] = append(out[g], s)
		} else {
			index[key] = len(out)
			out = append(out, []string{s})
		}
	}
	return out
}
