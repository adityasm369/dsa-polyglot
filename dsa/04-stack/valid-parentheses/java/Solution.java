import java.util.ArrayDeque;
import java.util.Deque;

/**
 * valid-parentheses. Time O(n), Space O(n).
 *
 * Java's old java.util.Stack extends Vector and exposes indexing, so it is the
 * wrong tool: it is synchronised for no reason and lets callers reach past the
 * top. ArrayDeque used as a stack (push/pop/peek at the head) is the modern
 * idiom, and the Javadoc for Stack itself recommends it.
 */
public final class Solution {
    private Solution() { }

    public static boolean isValid(String s) {
        if (s == null) return false;
        Deque<Character> stack = new ArrayDeque<>();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            switch (c) {
                case '(': case '[': case '{':
                    stack.push(c);
                    break;
                case ')': case ']': case '}': {
                    if (stack.isEmpty()) return false;   // pop() on empty throws
                    char open = stack.pop();
                    if ((c == ')' && open != '(') || (c == ']' && open != '[')
                            || (c == '}' && open != '{'))
                        return false;
                    break;
                }
                default:
                    return false;                         // outside the spec
            }
        }
        return stack.isEmpty();
    }
}
