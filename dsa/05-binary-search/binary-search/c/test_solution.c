#include "solution.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int checks = 0;

static void expect(const char *name, const int *a, size_t n, int t, ptrdiff_t want) {
    ptrdiff_t got = bsearch_index(a, n, t);
    if (got != want) { printf("  FAIL %-24s got %td want %td\n", name, got, want); assert(0); }
    if (got >= 0) assert(a[got] == t);
    printf("  PASS %-24s %td\n", name, got);
    checks++;
}

int main(void) {
    expect("empty array", NULL, 0, 5, -1);
    const int one[] = {5};
    expect("one element present", one, 1, 5, 0);
    expect("one element absent", one, 1, 3, -1);
    const int five[] = {1, 2, 3, 4, 5};
    expect("target is first", five, 5, 1, 0);
    expect("target is last", five, 5, 5, 4);
    const int three[] = {1, 2, 3};
    expect("absent below range", three, 3, 0, -1);
    expect("absent above range", three, 3, 9, -1);
    const int gap[] = {1, 3, 5, 7};
    expect("absent in a gap", gap, 4, 4, -1);
    const int two[] = {1, 2};
    expect("two elements", two, 2, 2, 1);
    const int neg[] = {-5, -3, -1};
    expect("negatives", neg, 3, -3, 1);
    const int ext[] = {INT_MIN, 0, INT_MAX};
    expect("extreme values", ext, 3, INT_MAX, 2);
    expect("extreme low", ext, 3, INT_MIN, 0);

    /* every index findable, every absent value rejected, 10k elements */
    size_t n = 10000;
    int *big = malloc(n * sizeof *big);
    for (size_t i = 0; i < n; i++) big[i] = (int)(i * 2);
    for (size_t i = 0; i < n; i++) {
        assert(bsearch_index(big, n, (int)(i * 2)) == (ptrdiff_t)i);
        assert(bsearch_index(big, n, (int)(i * 2 + 1)) == -1);
    }
    printf("  PASS %-24s\n", "10k: all found/rejected"); checks++;

    /* O(log n): 10,000 elements must take at most 14 iterations */
    int steps = 0;
    bsearch_counting(big, n, big[n - 1], &steps);
    assert(steps <= 14);
    printf("  PASS %-24s (%d steps for n=10000)\n", "is logarithmic", steps); checks++;
    free(big);

    /* Invariant 2: must terminate for every target on every small array. */
    for (size_t k = 0; k < 12; k++) {
        int small[12];
        for (size_t i = 0; i < k; i++) small[i] = (int)i;
        for (int t = -2; t < (int)k + 3; t++) bsearch_index(small, k, t);
    }
    printf("  PASS %-24s\n", "terminates everywhere"); checks++;

    printf("\n  %d checks passed\n", checks);
    return 0;
}
