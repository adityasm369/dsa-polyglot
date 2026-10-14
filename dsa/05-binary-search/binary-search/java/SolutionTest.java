import java.util.Arrays;

public final class SolutionTest {
    private static int checks = 0, failures = 0;

    private static void expect(String name, int[] a, int t, int want) {
        int[] before = a == null ? null : a.clone();
        int got = Solution.search(a, t);
        if (got != want) {
            System.out.printf("  FAIL %-24s got %d want %d%n", name, got, want);
            failures++; return;
        }
        if (got >= 0 && a[got] != t) { System.out.printf("  FAIL %-24s wrong index%n", name); failures++; return; }
        if (a != null && !Arrays.equals(a, before)) { System.out.printf("  FAIL %-24s input modified%n", name); failures++; return; }
        System.out.printf("  PASS %-24s %d%n", name, got);
        checks++;
    }

    public static void main(String[] args) {
        expect("empty array", new int[] {}, 5, -1);
        expect("null array", null, 5, -1);
        expect("one element present", new int[] {5}, 5, 0);
        expect("one element absent", new int[] {5}, 3, -1);
        expect("target is first", new int[] {1,2,3,4,5}, 1, 0);
        expect("target is last", new int[] {1,2,3,4,5}, 5, 4);
        expect("absent below range", new int[] {1,2,3}, 0, -1);
        expect("absent above range", new int[] {1,2,3}, 9, -1);
        expect("absent in a gap", new int[] {1,3,5,7}, 4, -1);
        expect("two elements", new int[] {1,2}, 2, 1);
        expect("negatives", new int[] {-5,-3,-1}, -3, 1);
        expect("extreme values", new int[] {Integer.MIN_VALUE, 0, Integer.MAX_VALUE},
               Integer.MAX_VALUE, 2);
        expect("extreme low", new int[] {Integer.MIN_VALUE, 0, Integer.MAX_VALUE},
               Integer.MIN_VALUE, 0);

        int[] big = new int[10000];
        for (int i = 0; i < big.length; i++) big[i] = i * 2;
        boolean allOk = true;
        for (int i = 0; i < big.length; i++) {
            if (Solution.search(big, i * 2) != i || Solution.search(big, i * 2 + 1) != -1) {
                allOk = false; break;
            }
        }
        if (!allOk) { System.out.println("  FAIL 10k sweep"); failures++; }
        else { System.out.printf("  PASS %-24s%n", "10k: all found/rejected"); checks++; }

        int steps = Solution.searchCounting(big, big[big.length - 1])[1];
        if (steps > 14) { System.out.printf("  FAIL is logarithmic: %d steps%n", steps); failures++; }
        else { System.out.printf("  PASS %-24s (%d steps for n=10000)%n", "is logarithmic", steps); checks++; }

        for (int k = 0; k < 12; k++) {        // invariant 2: must terminate
            int[] small = new int[k];
            for (int i = 0; i < k; i++) small[i] = i;
            for (int t = -2; t < k + 3; t++) Solution.search(small, t);
        }
        System.out.printf("  PASS %-24s%n", "terminates everywhere"); checks++;

        // THE BUG, demonstrated. These are plausible indices for a large array.
        int lo = 1 << 30, hi = (1 << 30) + 2;
        int broken = (lo + hi) / 2;          // wraps negative
        int correct = lo + (hi - lo) / 2;
        if (broken >= 0) { System.out.println("  FAIL expected (lo+hi)/2 to wrap"); failures++; }
        else {
            System.out.printf("  PASS %-24s (lo+hi)/2 = %d, safe form = %d%n",
                    "the JDK bug reproduced", broken, correct); checks++;
        }

        System.out.printf("%n  %d checks passed, %d failed%n", checks, failures);
        if (failures > 0) System.exit(1);
    }
}
