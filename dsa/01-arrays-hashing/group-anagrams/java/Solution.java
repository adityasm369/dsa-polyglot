import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * group-anagrams. Time O(n*k), Space O(n*k).
 *
 * The key is the 26 counts rendered as a String, not an int[]. That is not a
 * style choice: Java arrays inherit Object's identity hashCode and equals, so
 * two int[] holding the same numbers are different keys. new int[]{1} is never
 * equal to another new int[]{1}. Arrays.toString gives a value-based key;
 * List&lt;Integer&gt; would also work, since List defines equals by content.
 */
public final class Solution {
    private Solution() { }

    public static List<List<String>> groupAnagrams(String[] strs) {
        Map<String, List<String>> groups = new HashMap<>();
        List<List<String>> out = new ArrayList<>();
        if (strs == null) return out;

        for (String s : strs) {
            int[] counts = new int[26];
            for (int i = 0; i < s.length(); i++) {
                char c = s.charAt(i);
                if (c >= 'a' && c <= 'z') counts[c - 'a']++;
            }
            String key = Arrays.toString(counts);   // value-based, unlike the array
            List<String> group = groups.get(key);
            if (group == null) {
                group = new ArrayList<>();
                groups.put(key, group);
                out.add(group);                     // preserves first-appearance order
            }
            group.add(s);
        }
        return out;
    }
}
