import java.util.Arrays;
import java.util.Optional;

/**
 * Tests from SPEC.md. Plain assertions and a main method rather than JUnit:
 * the repo must compile with nothing but a JDK, and a student can read the
 * whole harness. Run with: javac *.java && java SolutionTest
 */
public final class SolutionTest {
    private static int checks = 0;
    private static int failures = 0;

    private static void expect(String name, int[] nums, long target, int wi, int wj) {
        int[] before = nums.clone();
        Optional<int[]> got = Solution.twoSum(nums, target);
        if (got.isEmpty() || got.get()[0] != wi || got.get()[1] != wj) {
            System.out.printf("  FAIL %-26s got %s, want (%d,%d)%n",
                    name, got.map(Arrays::toString).orElse("empty"), wi, wj);
            failures++;
            return;
        }
        int i = got.get()[0], j = got.get()[1];
        check(name, i < j, "indices ordered");
        check(name, (long) nums[i] + nums[j] == target, "pair sums to target");
        check(name, Arrays.equals(nums, before), "input not modified");
        System.out.printf("  PASS %-26s (%d,%d)%n", name, i, j);
        checks++;
    }

    private static void check(String name, boolean cond, String what) {
        if (!cond) { System.out.printf("  FAIL %-26s %s%n", name, what); failures++; }
    }

    public static void main(String[] args) {
        expect("minimum size",          new int[] {1, 2},             3,  0, 1);
        expect("answer at the ends",    new int[] {3, 2, 4, 1},       4,  0, 3);
        expect("duplicate values",      new int[] {3, 3},             6,  0, 1);
        expect("same value, one pair",  new int[] {3, 2, 3},          6,  0, 2);
        expect("negatives",             new int[] {-1, -2, -3, -4},  -6,  1, 3);
        expect("zero target and zeros", new int[] {0, 0},             0,  0, 1);
        expect("overflow guard",
               new int[] {1000000000, 1000000000}, 2000000000L, 0, 1);
        expect("answer in the middle",  new int[] {1, 5, 2, 7, 3},    9,  2, 3);

        check("no pair", Solution.twoSum(new int[] {1, 2, 3}, 100).isEmpty(), "empty");
        System.out.printf("  PASS %-26s%n", "no pair -> empty"); checks++;
        check("null input", Solution.twoSum(null, 1).isEmpty(), "empty");
        check("n<2", Solution.twoSum(new int[] {1}, 1).isEmpty(), "empty");
        System.out.printf("  PASS %-26s%n", "null and n<2 refused"); checks++;

        // The overflow this guards against, shown rather than asserted: with
        // int arithmetic 2000000000 - (-2000000000) wraps negative.
        int a = 2000000000, b = -2000000000;
        check("int really does wrap", a - b < 0, "int32 wraps as documented");
        System.out.printf("  PASS %-26s (int: %d, long: %d)%n",
                "int32 wrap demonstrated", a - b, (long) a - b); checks++;

        int[] big = new int[2000];
        for (int i = 0; i < 2000; i++) big[i] = i;
        expect("2000 keys", big, 1999 + 1998, 1998, 1999);

        System.out.printf("%n  %d checks passed, %d failed%n", checks, failures);
        if (failures > 0) System.exit(1);
    }
}
