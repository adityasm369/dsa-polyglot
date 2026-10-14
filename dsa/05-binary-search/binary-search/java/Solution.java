/**
 * binary-search. Time O(log n), Space O(1).
 *
 * THIS is the bug. Joshua Bloch found (low + high) / 2 in
 * java.util.Arrays.binarySearch in 2006; it had shipped since JDK 1.2, nine
 * years, in a method every Java programmer called without a second thought.
 * Java's int silently wraps NEGATIVE on overflow, so mid becomes negative and
 * the array access throws ArrayIndexOutOfBoundsException -- a crash, in a
 * sorted-array lookup, on a large enough array.
 *
 * Bloch's write-up: "Nearly All Binary Searches and Mergesorts Are Broken".
 * SolutionTest demonstrates the wrap rather than describing it.
 */
public final class Solution {
    private Solution() { }

    /** @return the index of target, or -1. nums is not modified. */
    public static int search(int[] nums, int target) {
        if (nums == null || nums.length == 0) return -1;
        int lo = 0, hi = nums.length - 1;
        while (lo <= hi) {                 // <=, not <: [5] must be searchable
            int mid = lo + (hi - lo) / 2;  // NOT (lo + hi) / 2 -- see above
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) lo = mid + 1;
            else hi = mid - 1;
        }
        return -1;
    }

    /** Index and iteration count, for the O(log n) teaching note. */
    public static int[] searchCounting(int[] nums, int target) {
        int steps = 0;
        if (nums == null || nums.length == 0) return new int[] { -1, 0 };
        int lo = 0, hi = nums.length - 1;
        while (lo <= hi) {
            steps++;
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target) return new int[] { mid, steps };
            if (nums[mid] < target) lo = mid + 1;
            else hi = mid - 1;
        }
        return new int[] { -1, steps };
    }
}
