public final class SolutionTest {
    private static int checks = 0, failures = 0;

    private static void expect(String name, String s, boolean want) {
        boolean got = Solution.isPalindrome(s);
        if (got != want) {
            System.out.printf("  FAIL %-24s got %b want %b%n", name, got, want);
            failures++; return;
        }
        System.out.printf("  PASS %-24s %b%n", name, want);
        checks++;
    }

    public static void main(String[] args) {
        expect("empty", "", true);
        expect("one character", "a", true);
        expect("only punctuation", ".,!", true);
        expect("mixed case", "Aa", true);
        expect("digits count", "0P", false);
        expect("the textbook one", "A man, a plan, a canal: Panama", true);
        expect("nearly", "race a car", false);
        expect("all skipped but one", "...a...", true);
        expect("spaces only", "   ", true);
        expect("digits palindrome", "12321", true);
        expect("digits not", "12345", false);
        expect("null is accepted", null, true);
        expect("200k characters", "a".repeat(200000), true);

        // Strings are immutable in Java, so invariant 2 holds by construction.
        String s = "A man, a plan";
        Solution.isPalindrome(s);
        expect("input unchanged", s, false);   // "A man, a plan" is not one

        System.out.printf("%n  %d checks passed, %d failed%n", checks, failures);
        if (failures > 0) System.exit(1);
    }
}
