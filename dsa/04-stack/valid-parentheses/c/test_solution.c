#include "solution.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static int checks = 0;

static void expect(const char *name, const char *s, int want) {
    int got = is_valid(s, strlen(s));
    if (got != want) { printf("  FAIL %-20s got %d want %d\n", name, got, want); assert(0); }
    printf("  PASS %-20s %s\n", name, want ? "valid" : "invalid");
    checks++;
}

int main(void) {
    expect("single opener", "(", 0);
    expect("single closer", ")", 0);
    expect("simple", "()", 1);
    expect("all three types", "()[]{}", 1);
    expect("nested", "([{}])", 1);
    expect("interleaved", "([)]", 0);
    expect("closes too early", ")(", 0);
    expect("left open", "(((", 0);
    expect("empty string", "", 1);
    /* a real NULL pointer, not an empty string: the function must refuse it */
    assert(is_valid(NULL, 0) == 0);
    printf("  PASS %-20s NULL pointer\n", "null is invalid"); checks++;

    /* 5000 nested pairs: iterative, so no recursion depth to exhaust. */
    char big[10001];
    memset(big, '(', 5000);
    memset(big + 5000, ')', 5000);
    big[10000] = '\0';
    assert(is_valid(big, 10000) == 1);
    printf("  PASS %-20s 5000 nested pairs\n", "long balanced"); checks++;

    printf("\n  %d checks passed\n", checks);
    return 0;
}
