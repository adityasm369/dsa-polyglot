// Package climbingstairs solves climbing-stairs. Time O(n), Space O(1).
//
// int64 for the accumulator. On a 64-bit platform `int` is already 64 bits, but
// writing int64 states the width the answer needs rather than relying on the
// host, the same reasoning as the two-sum solution.
package climbingstairs

// ClimbStairs returns the number of distinct ways to climb n steps, 1 or 2 at a time.
func ClimbStairs(n int) int64 {
	if n <= 2 {
		if n < 1 {
			return 0
		}
		return int64(n)
	}
	var prev, cur int64 = 1, 2
	for i := 3; i <= n; i++ {
		prev, cur = cur, prev+cur // the last move was a 1 or a 2
	}
	return cur
}
