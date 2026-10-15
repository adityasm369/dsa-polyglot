public final class SolutionTest {
    private static int checks = 0, failures = 0;

    private static void expect(String name, String s, boolean want) {
        boolean got = Solution.isValid(s);
        if (got != want) { System.out.printf("  FAIL %-20s got %b%n", name, got); failures++; return; }
        System.out.printf("  PASS %-20s %s%n", name, want ? "valid" : "invalid");
        checks++;
    }

    public static void main(String[] args) {
        expect("single opener", "(", false);
        expect("single closer", ")", false);
        expect("simple", "()", true);
        expect("all three types", "()[]{}", true);
        expect("nested", "([{}])", true);
        expect("interleaved", "([)]", false);
        expect("closes too early", ")(", false);
        expect("left open", "(((", false);
        expect("empty string", "", true);
        expect("null is invalid", null, false);
        expect("long balanced", "(".repeat(5000) + ")".repeat(5000), true);

        System.out.printf("%n  %d checks passed, %d failed%n", checks, failures);
        if (failures > 0) System.exit(1);
    }
}
