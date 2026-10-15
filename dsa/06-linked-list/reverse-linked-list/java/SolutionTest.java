import java.util.ArrayList;
import java.util.List;

public final class SolutionTest {
    private static int checks = 0, failures = 0;
    private static final int N_LONG = 100000;

    private static Solution.ListNode build(int[] values) {
        Solution.ListNode head = null;
        for (int i = values.length - 1; i >= 0; i--) head = new Solution.ListNode(values[i], head);
        return head;
    }

    private static List<Integer> collect(Solution.ListNode head) {
        List<Integer> out = new ArrayList<>();
        for (Solution.ListNode n = head; n != null; n = n.next) out.add(n.val);
        return out;
    }

    private static void expect(String name, int[] in, List<Integer> want) {
        Solution.ListNode orig = build(in);
        List<Integer> got = collect(Solution.reverse(orig));
        if (!got.equals(want)) {
            System.out.printf("  FAIL %-22s got %s want %s%n", name, got, want);
            failures++; return;
        }
        if (in.length > 0 && orig.next != null) {          // invariant 2
            System.out.printf("  FAIL %-22s old head still linked%n", name);
            failures++; return;
        }
        System.out.printf("  PASS %-22s len %d%n", name, in.length);
        checks++;
    }

    public static void main(String[] args) {
        expect("empty", new int[] {}, List.of());
        expect("one node", new int[] {1}, List.of(1));
        expect("two nodes", new int[] {1, 2}, List.of(2, 1));
        expect("odd length", new int[] {1, 2, 3}, List.of(3, 2, 1));
        expect("negatives and zero", new int[] {-1, 0, 1}, List.of(1, 0, -1));

        Solution.ListNode h = build(new int[] {1, 2, 3});
        h = Solution.reverse(Solution.reverse(h));
        if (collect(h).equals(List.of(1, 2, 3))) {
            System.out.printf("  PASS %-22s%n", "reverse twice"); checks++;
        } else { System.out.println("  FAIL reverse twice"); failures++; }

        // 100,000 nodes. Java's default stack holds roughly 10,000-20,000 frames,
        // so a RECURSIVE reverse throws StackOverflowError here. The iterative
        // one does not.
        int[] big = new int[N_LONG];
        for (int i = 0; i < N_LONG; i++) big[i] = i;
        try {
            Solution.ListNode lst = Solution.reverse(build(big));
            if (lst.val == N_LONG - 1) { System.out.printf("  PASS %-22s%n", "100k nodes, no overflow"); checks++; }
            else { System.out.println("  FAIL 100k wrong head"); failures++; }
        } catch (StackOverflowError e) {
            System.out.println("  FAIL 100k: stack overflow"); failures++;
        }

        System.out.printf("%n  %d checks passed, %d failed%n", checks, failures);
        if (failures > 0) System.exit(1);
    }
}
