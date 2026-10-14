package binarysearch

import (
	"math"
	"math/bits"
	"slices"
	"testing"
)

const intMin, intMax = math.MinInt32, math.MaxInt32

func TestSpecCases(t *testing.T) {
	cases := []struct {
		name   string
		nums   []int
		target int
		want   int
	}{
		{"empty array", []int{}, 5, -1},
		{"one element present", []int{5}, 5, 0},
		{"one element absent", []int{5}, 3, -1},
		{"target is first", []int{1, 2, 3, 4, 5}, 1, 0},
		{"target is last", []int{1, 2, 3, 4, 5}, 5, 4},
		{"absent below range", []int{1, 2, 3}, 0, -1},
		{"absent above range", []int{1, 2, 3}, 9, -1},
		{"absent in a gap", []int{1, 3, 5, 7}, 4, -1},
		{"two elements", []int{1, 2}, 2, 1},
		{"negatives", []int{-5, -3, -1}, -3, 1},
		{"extreme values", []int{intMin, 0, intMax}, intMax, 2},
		{"extreme low", []int{intMin, 0, intMax}, intMin, 0},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			before := slices.Clone(c.nums)
			got := Search(c.nums, c.target)
			if got != c.want {
				t.Fatalf("got %d, want %d", got, c.want)
			}
			if got != -1 && c.nums[got] != c.target {
				t.Errorf("index %d does not hold the target", got)
			}
			if !slices.Equal(c.nums, before) {
				t.Error("input was modified")
			}
		})
	}
}

func TestEveryIndexFindable(t *testing.T) {
	nums := make([]int, 10000)
	for i := range nums {
		nums[i] = i * 2
	}
	for i, v := range nums {
		if got := Search(nums, v); got != i {
			t.Fatalf("Search(%d) = %d, want %d", v, got, i)
		}
		if got := Search(nums, v+1); got != -1 {
			t.Fatalf("Search(%d) = %d, want -1", v+1, got)
		}
	}
}

func TestIsLogarithmic(t *testing.T) {
	nums := make([]int, 10000)
	for i := range nums {
		nums[i] = i
	}
	limit := bits.Len(uint(len(nums))) // ceil(log2(n+1))
	for _, v := range []int{0, 5000, 9999} {
		if _, steps := SearchCounting(nums, v); steps > limit {
			t.Errorf("%d steps for %d, limit %d", steps, v, limit)
		}
	}
}

// Invariant 2: the range must shrink every iteration. If it does not, this
// hangs -- which is the honest way to discover it.
func TestTerminatesEverywhere(t *testing.T) {
	for n := 0; n < 12; n++ {
		nums := make([]int, n)
		for i := range nums {
			nums[i] = i
		}
		for target := -2; target < n+3; target++ {
			Search(nums, target)
		}
	}
}
