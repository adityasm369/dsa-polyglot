/* valid-parentheses. Time O(n), Space O(n).
 *
 * C has no stack type, so the stack is a fixed array with a top index. The
 * capacity is n: the stack never holds more openers than there are characters.
 * The array is malloc'd, so this is the one place in this folder where memory
 * ownership is explicit -- freed on every return path.
 */
#include "solution.h"
#include <stdlib.h>

static char matching_opener(char closer) {
    switch (closer) {
        case ')': return '(';
        case ']': return '[';
        case '}': return '{';
        default:  return 0;
    }
}

int is_valid(const char *s, size_t n) {
    if (!s) return 0;
    if (n == 0) return 1;
    char *stack = malloc(n);
    if (!stack) return 0;
    size_t top = 0;
    int ok = 1;
    for (size_t i = 0; i < n && ok; i++) {
        char c = s[i];
        char want = matching_opener(c);
        if (want == 0) {                       /* an opener */
            stack[top++] = c;
        } else if (top == 0 || stack[--top] != want) {
            ok = 0;                            /* empty stack, or wrong type */
        }
    }
    if (ok && top != 0) ok = 0;                /* openers left open */
    free(stack);
    return ok;
}
