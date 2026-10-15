/**
 * climbing-stairs. Time O(n), Space O(1).
 *
 * long, not int. The answer for n = 45 fits in an int, but Java int arithmetic
 * wraps silently past 2^31 - 1: the answer for n = 46 is 2971215073, which is
 * negative as an int. Nothing warns you. See SolutionTest for the demonstration.
 */
public final class Solution {
    private Solution() { }

    public static long climbStairs(int n) {
        if (n <= 2) return n < 1 ? 0 : n;      // ways(1)=1, ways(2)=2
        long prev = 1, cur = 2;
        for (int i = 3; i <= n; i++) {
            long next = prev + cur;            // the last move was a 1 or a 2
            prev = cur;
            cur = next;
        }
        return cur;
    }
}
