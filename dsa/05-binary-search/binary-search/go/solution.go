// Package binarysearch solves binary-search. Time O(log n), Space O(1).
//
// Go's `int` is 64-bit on every platform this repo targets, so (lo+hi)/2 needs
// an array of about 4.6 quintillion elements before it overflows -- which is to
// say never. Go is safe here by accident of word size, not by design: on a
// 32-bit build `int` is 32 bits and the JDK bug applies exactly.
//
// The safe form is used regardless. A habit that depends on the target
// architecture is not a habit.
package binarysearch

// Search returns the index of target in the ascending, duplicate-free nums, or
// -1. nums is not modified -- it is read through a slice header, and nothing
// here writes through it.
func Search(nums []int, target int) int {
	lo, hi := 0, len(nums)-1
	for lo <= hi { // <=, not <: a one-element range must still be searched
		mid := lo + (hi-lo)/2
		switch {
		case nums[mid] == target:
			return mid
		case nums[mid] < target:
			lo = mid + 1 // mid is ruled out, so the range must exclude it
		default:
			hi = mid - 1
		}
	}
	return -1
}

// SearchCounting returns the index and the number of iterations, for the
// teaching note about what O(log n) actually means.
func SearchCounting(nums []int, target int) (int, int) {
	lo, hi, steps := 0, len(nums)-1, 0
	for lo <= hi {
		steps++
		mid := lo + (hi-lo)/2
		switch {
		case nums[mid] == target:
			return mid, steps
		case nums[mid] < target:
			lo = mid + 1
		default:
			hi = mid - 1
		}
	}
	return -1, steps
}
