import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

/**
 * two-sum. Time O(n) average, Space O(n).
 *
 * Two Java-specific costs a fourth-year should be able to name:
 *
 * 1. HashMap&lt;Long, Integer&gt; stores OBJECTS, not primitives. Every put
 *    autoboxes an int into an Integer on the heap. For n = 10^4 that is 10^4
 *    allocations the C and C++ versions never make. This is why Java loses to
 *    C++ on tight numeric loops, and why Valhalla (value types) is being built.
 *
 * 2. long, not int, for the arithmetic. nums[i] reaches 1e9 and target reaches
 *    2e9, so {@code target - nums[j]} overflows int silently -- Java has no
 *    overflow trap, it just wraps. SPEC.md's overflow case fails without this.
 */
public final class Solution {
    private Solution() { }

    /** @return the two indices, i &lt; j, or empty if no pair exists. */
    public static Optional<int[]> twoSum(int[] nums, long target) {
        if (nums == null || nums.length < 2) return Optional.empty();

        // Sized for the load factor: HashMap resizes at 0.75 capacity, and
        // rehashing mid-loop is avoidable work.
        Map<Long, Integer> seen = new HashMap<>(nums.length * 2);
        for (int j = 0; j < nums.length; j++) {
            long want = target - (long) nums[j];
            Integer i = seen.get(want);
            if (i != null) return Optional.of(new int[] { i, j });
            // putIfAbsent, not put: on a duplicate the first index must win, so
            // [3,3] gives (0,1) rather than (1,1).
            seen.putIfAbsent((long) nums[j], j);
        }
        return Optional.empty();
    }
}
