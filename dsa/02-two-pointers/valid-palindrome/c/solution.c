/* valid-palindrome. Time O(n), Space O(1).
 *
 * A C string has no length: it ends at the first zero byte, so strlen walks the
 * whole thing to find the end before the algorithm can start. That is an extra
 * O(n) pass every other language here avoids, and it is the oldest performance
 * trap in C.
 */
#include "solution.h"
#include <ctype.h>
#include <string.h>

/* isalnum and tolower take an INT whose value must be representable as an
 * unsigned char, or be EOF. Passing a plain `char` is undefined behaviour when
 * char is signed and the byte is >= 0x80 -- which it is for any non-ASCII input.
 * This is a real bug that ships; the cast is not decoration. */
static int alnum(unsigned char c) { return isalnum(c); }
static int lower(unsigned char c) { return tolower(c); }

int is_palindrome(const char *s) {
    if (!s) return 1;                  /* no string is vacuously symmetric */
    size_t i = 0, j = strlen(s);
    if (j == 0) return 1;
    j--;
    while (i < j) {
        /* Both skips re-check i < j, or ".,!" runs the pointers past each
         * other and, with size_t being UNSIGNED, j-- at zero wraps to SIZE_MAX
         * and reads wildly out of bounds. In C this bug is not a wrong answer,
         * it is a segfault. */
        while (i < j && !alnum((unsigned char)s[i])) i++;
        while (i < j && !alnum((unsigned char)s[j])) j--;
        if (lower((unsigned char)s[i]) != lower((unsigned char)s[j])) return 0;
        i++;
        if (j == 0) break;             /* cannot decrement an unsigned zero */
        j--;
    }
    return 1;
}
