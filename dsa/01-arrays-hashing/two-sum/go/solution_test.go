package twosum

import (
	"slices"
	"testing"
)

// Cases from SPEC.md. Table-driven, which is the Go convention and happens to
// read as a specification.
func TestSpecCases(t *testing.T) {
	cases := []struct {
		name   string
		nums   []int
		target int64
		wi, wj int
	}{
		{"minimum size", []int{1, 2}, 3, 0, 1},
		{"answer at the ends", []int{3, 2, 4, 1}, 4, 0, 3},
		{"duplicate values", []int{3, 3}, 6, 0, 1},
		{"same value, one pair", []int{3, 2, 3}, 6, 0, 2},
		{"negatives", []int{-1, -2, -3, -4}, -6, 1, 3},
		{"zero target and zeros", []int{0, 0}, 0, 0, 1},
		{"overflow guard", []int{1000000000, 1000000000}, 2000000000, 0, 1},
		{"answer in the middle", []int{1, 5, 2, 7, 3}, 9, 2, 3},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			before := slices.Clone(c.nums)
			i, j, ok := TwoSum(c.nums, c.target)
			if !ok || i != c.wi || j != c.wj {
				t.Fatalf("got (%d,%d,%v), want (%d,%d,true)", i, j, ok, c.wi, c.wj)
			}
			if i >= j {
				t.Errorf("indices not ordered: %d >= %d", i, j)
			}
			if int64(c.nums[i])+int64(c.nums[j]) != c.target {
				t.Errorf("pair does not sum to target")
			}
			if !slices.Equal(c.nums, before) {
				t.Errorf("input was modified")
			}
		})
	}
}

func TestNoPair(t *testing.T) {
	if _, _, ok := TwoSum([]int{1, 2, 3}, 100); ok {
		t.Error("expected ok=false when no pair exists")
	}
}

func TestTooShort(t *testing.T) {
	for _, n := range [][]int{{}, {1}} {
		if _, _, ok := TwoSum(n, 1); ok {
			t.Errorf("expected ok=false for %v", n)
		}
	}
}

// The comma-ok idiom is what makes index 0 safe; this pins it.
func TestZeroIndexIsNotMistakenForAbsent(t *testing.T) {
	i, j, ok := TwoSum([]int{0, 4}, 4)
	if !ok || i != 0 || j != 1 {
		t.Fatalf("got (%d,%d,%v), want (0,1,true)", i, j, ok)
	}
}

func TestManyKeys(t *testing.T) {
	big := make([]int, 2000)
	for i := range big {
		big[i] = i
	}
	i, j, ok := TwoSum(big, 1999+1998)
	if !ok || i != 1998 || j != 1999 {
		t.Fatalf("got (%d,%d,%v), want (1998,1999,true)", i, j, ok)
	}
}

func BenchmarkTwoSum(b *testing.B) {
	big := make([]int, 10000)
	for i := range big {
		big[i] = i
	}
	b.ResetTimer()
	for n := 0; n < b.N; n++ {
		TwoSum(big, 19997)
	}
}
