/**
 * valid-palindrome. Time O(n), Space O(1).
 *
 * A Java String is UTF-16, so charAt(i) returns a 16-bit code UNIT, not a
 * character. For the ASCII this spec allows they are the same thing; above
 * U+FFFF one character takes two units and charAt returns half of it. The
 * correct general form walks code points, and nobody does.
 *
 * Character.isLetterOrDigit is Unicode-aware, so it accepts far more than
 * [a-zA-Z0-9] -- Devanagari digits, for instance. That is a DIFFERENT rule from
 * the C version's isalnum, which is locale-dependent ASCII. Under this spec's
 * ASCII constraint they agree; the moment the constraint lifts they do not, and
 * that divergence is the lesson.
 */
public final class Solution {
    private Solution() { }

    public static boolean isPalindrome(String s) {
        if (s == null || s.isEmpty()) return true;
        int i = 0, j = s.length() - 1;
        while (i < j) {
            // Each skip re-checks i < j, or ".,!" runs the indices past each
            // other and charAt throws StringIndexOutOfBoundsException.
            while (i < j && !Character.isLetterOrDigit(s.charAt(i))) i++;
            while (i < j && !Character.isLetterOrDigit(s.charAt(j))) j--;
            if (Character.toLowerCase(s.charAt(i)) != Character.toLowerCase(s.charAt(j)))
                return false;
            i++; j--;
        }
        return true;
    }
}
