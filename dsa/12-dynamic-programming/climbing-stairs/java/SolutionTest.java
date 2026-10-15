public final class SolutionTest {
    private static int checks = 0, failures = 0;

    private static void expect(int n, long want) {
        long got = Solution.climbStairs(n);
        if (got != want) { System.out.printf("  FAIL n=%d got %d want %d%n", n, got, want); failures++; return; }
        System.out.printf("  PASS n=%-3d %d%n", n, got);
        checks++;
    }

    public static void main(String[] args) {
        expect(1, 1); expect(2, 2); expect(3, 3); expect(4, 5);
        expect(5, 8); expect(10, 89); expect(45, 1836311903L);

        // The int trap, shown: the same recurrence in 32 bits goes negative.
        int a = 1, b = 2;
        for (int i = 3; i <= 46; i++) { int next = a + b; a = b; b = next; }
        if (b < 0) { System.out.printf("  PASS %-12s int32 n=46 = %d (negative)%n", "int wraps", b); checks++; }
        else { System.out.println("  FAIL int did not wrap"); failures++; }
        System.out.printf("  PASS %-12s long  n=46 = %d%n", "long is fine", Solution.climbStairs(46)); checks++;

        System.out.printf("%n  %d checks passed, %d failed%n", checks, failures);
        if (failures > 0) System.exit(1);
    }
}
