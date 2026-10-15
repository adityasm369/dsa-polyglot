public final class SolutionTest {
    private static int checks = 0, failures = 0;

    private static Solution.ListNode[] build(int... values) {
        Solution.ListNode[] ns = new Solution.ListNode[values.length];
        for (int i = 0; i < values.length; i++) ns[i] = new Solution.ListNode(values[i]);
        for (int i = 0; i + 1 < ns.length; i++) ns[i].next = ns[i + 1];
        return ns;
    }

    private static void check(String name, boolean got, boolean want) {
        if (got != want) { System.out.printf("  FAIL %-26s got %b%n", name, got); failures++; return; }
        System.out.printf("  PASS %-26s %s%n", name, want ? "cycle" : "no cycle");
        checks++;
    }

    public static void main(String[] args) {
        check("empty", Solution.hasCycle(null), false);

        check("one node, no cycle", Solution.hasCycle(build(1)[0]), false);
        check("two nodes, no cycle", Solution.hasCycle(build(1, 2)[0]), false);

        Solution.ListNode[] self = build(1);
        self[0].next = self[0];
        check("one node, self-loop", Solution.hasCycle(self[0]), true);

        Solution.ListNode[] three = build(1, 2, 3);
        three[2].next = three[0];
        check("cycle back to head", Solution.hasCycle(three[0]), true);

        Solution.ListNode[] four = build(1, 2, 3, 4);
        four[3].next = four[1];
        check("cycle to middle", Solution.hasCycle(four[0]), true);

        check("equal values, no cycle", Solution.hasCycle(build(7, 7, 7, 7)[0]), false);

        int[] v = new int[10000];
        for (int i = 0; i < v.length; i++) v[i] = i;
        Solution.ListNode[] big = build(v);
        check("long, no cycle", Solution.hasCycle(big[0]), false);
        big[big.length - 1].next = big[0];
        check("long, cycle at end", Solution.hasCycle(big[0]), true);

        System.out.printf("%n  %d checks passed, %d failed%n", checks, failures);
        if (failures > 0) System.exit(1);
    }
}
