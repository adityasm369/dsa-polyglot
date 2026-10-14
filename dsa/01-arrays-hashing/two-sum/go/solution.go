// Package twosum solves two-sum. Time O(n) average, Space O(n).
//
// Two Go idioms a fourth-year should take away:
//
//  1. The comma-ok lookup. `i, ok := seen[want]` distinguishes "absent" from
//     "present and zero" in one line. In a problem whose valid answer includes
//     index 0, that distinction is the bug in the JavaScript version's
//     `if (map[k])`.
//  2. Multiple return values instead of an optional type. Go has no Optional
//     and no exceptions here; "no answer" is a third return value the caller
//     cannot ignore without the compiler noticing an unused variable.
package twosum

// TwoSum returns the two indices i < j such that nums[i]+nums[j] == target,
// and ok=false if no such pair exists. nums is not modified.
//
// target is int64 because nums values reach 1e9, so the sum reaches 2e9 --
// outside int32. Go's `int` is 64-bit on every platform this repo targets, but
// being explicit documents the requirement rather than relying on the host.
func TwoSum(nums []int, target int64) (int, int, bool) {
	if len(nums) < 2 {
		return 0, 0, false
	}
	seen := make(map[int64]int, len(nums)) // value -> first index seen at
	for j, x := range nums {
		want := target - int64(x)
		if i, ok := seen[want]; ok {
			return i, j, true // i was stored at an earlier j, so i < j
		}
		// Only if absent: on duplicates the first index must win, so [3,3]
		// gives (0,1). Go has no putIfAbsent, so the check is explicit.
		if _, exists := seen[int64(x)]; !exists {
			seen[int64(x)] = j
		}
	}
	return 0, 0, false
}
