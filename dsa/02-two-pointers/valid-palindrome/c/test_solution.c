#include "solution.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* strdup is POSIX, not C17. Under -std=c17 it is not declared, so the compiler
 * assumed it returned int, truncated the pointer and the test segfaulted. The
 * fix is not to add _POSIX_C_SOURCE: invariant 2 (input not modified) is
 * already PROVEN by the signature -- is_palindrome takes `const char *`, so a
 * mutation would not compile. That is the same guarantee Rust's &str gives,
 * and C gets it here for free. Nothing to copy, nothing to compare. */

static int checks = 0;

static void expect(const char *name, const char *s, int want) {
    int got = is_palindrome(s);
    if (got != want) { printf("  FAIL %-24s got %d want %d\n", name, got, want); assert(0); }
    printf("  PASS %-24s %s\n", name, want ? "true" : "false");
    checks++;
}

int main(void) {
    expect("empty", "", 1);
    expect("one character", "a", 1);
    expect("only punctuation", ".,!", 1);
    expect("mixed case", "Aa", 1);
    expect("digits count", "0P", 0);
    expect("the textbook one", "A man, a plan, a canal: Panama", 1);
    expect("nearly", "race a car", 0);
    expect("all skipped but one", "...a...", 1);
    expect("spaces only", "   ", 1);
    expect("digits palindrome", "12321", 1);
    expect("digits not", "12345", 0);
    expect("null is accepted", NULL, 1);

    /* 200k characters: the constraint's upper bound, and a stack-free path */
    size_t n = 200000;
    char *big = malloc(n + 1);
    for (size_t k = 0; k < n; k++) big[k] = 'a';
    big[n] = '\0';
    expect("200k characters", big, 1);
    free(big);

    printf("\n  %d checks passed\n", checks);
    return 0;
}
