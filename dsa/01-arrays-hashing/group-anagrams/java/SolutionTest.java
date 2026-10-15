import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public final class SolutionTest {
    private static int checks = 0, failures = 0;

    private static boolean isAnagram(String a, String b) {
        char[] x = a.toCharArray(), y = b.toCharArray();
        Arrays.sort(x);
        Arrays.sort(y);
        return Arrays.equals(x, y);
    }

    private static void checkPartition(String name, String[] strs, int wantGroups) {
        List<List<String>> groups = Solution.groupAnagrams(strs);
        if (groups.size() != wantGroups) {
            System.out.printf("  FAIL %-26s got %d groups, want %d%n", name, groups.size(), wantGroups);
            failures++;
            return;
        }
        // Invariant 1: every string appears exactly once.
        List<String> flat = new ArrayList<>();
        for (List<String> g : groups) flat.addAll(g);
        List<String> want = new ArrayList<>(Arrays.asList(strs));
        Collections.sort(flat);
        Collections.sort(want);
        if (!flat.equals(want)) {
            System.out.printf("  FAIL %-26s strings lost or duplicated%n", name);
            failures++;
            return;
        }
        // Invariant 2, both directions.
        for (int gi = 0; gi < groups.size(); gi++) {
            for (String a : groups.get(gi)) {
                for (String b : groups.get(gi)) {
                    if (!isAnagram(a, b)) { System.out.printf("  FAIL %-26s merged%n", name); failures++; return; }
                }
                for (int gj = 0; gj < groups.size(); gj++) {
                    if (gi == gj) continue;
                    for (String b : groups.get(gj)) {
                        if (isAnagram(a, b)) { System.out.printf("  FAIL %-26s split%n", name); failures++; return; }
                    }
                }
            }
        }
        System.out.printf("  PASS %-26s %d strings, %d groups%n", name, strs.length, groups.size());
        checks++;
    }

    public static void main(String[] args) {
        checkPartition("single string", new String[]{"a"}, 1);
        checkPartition("empty string", new String[]{""}, 1);
        checkPartition("all empty", new String[]{"", ""}, 1);
        checkPartition("no anagrams", new String[]{"abc", "def"}, 2);
        checkPartition("classic", new String[]{"eat", "tea", "tan", "ate", "nat", "bat"}, 3);
        checkPartition("same letters diff counts", new String[]{"aab", "abb"}, 2);
        checkPartition("repeated string", new String[]{"ab", "ab"}, 1);
        checkPartition("empty mixed in", new String[]{"eat", "tea", "tan", "ate", "nat", "bat", "", "aab"}, 5);
        // null is checked directly: the partition helper dereferences strs.
        if (Solution.groupAnagrams(null).isEmpty()) {
            System.out.printf("  PASS %-26s empty list, no throw%n", "null input");
            checks++;
        } else {
            System.out.println("  FAIL null input did not return an empty list");
            failures++;
        }

        // Why the key is a String: an int[] key does not work, and nothing warns you.
        Map<int[], String> byArray = new HashMap<>();
        byArray.put(new int[]{1, 2}, "x");
        if (byArray.get(new int[]{1, 2}) == null) {
            System.out.printf("  PASS %-26s int[] key lookup returns null%n", "array keys are identity");
            checks++;
        } else {
            System.out.println("  FAIL int[] key unexpectedly matched");
            failures++;
        }

        System.out.printf("%n  %d checks passed, %d failed%n", checks, failures);
        if (failures > 0) System.exit(1);
    }
}
