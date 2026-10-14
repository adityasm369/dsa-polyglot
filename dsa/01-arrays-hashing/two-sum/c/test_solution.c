/* Tests from SPEC.md. No framework: assert.h is in the standard library and a
 * fourth-year should see that a test is just a program that exits non-zero. */
#include "solution.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static int checks = 0;

static void expect(const char *name, const int *nums, size_t n, long long target,
                   int want_i, int want_j) {
    int i = -1, j = -1;
    int ok = two_sum(nums, n, target, &i, &j);
    if (!ok || i != want_i || j != want_j) {
        printf("  FAIL %-26s got (%d,%d) ok=%d, want (%d,%d)\n",
               name, i, j, ok, want_i, want_j);
        assert(0);
    }
    assert(i < j);                                   /* invariant 1 */
    assert((long long)nums[i] + nums[j] == target);  /* the pair really sums */
    printf("  PASS %-26s (%d,%d)\n", name, i, j);
    checks++;
}

int main(void) {
    const int a[] = {1, 2};                 expect("minimum size", a, 2, 3, 0, 1);
    const int b[] = {3, 2, 4, 1};           expect("answer at the ends", b, 4, 4, 0, 3);
    const int c[] = {3, 3};                 expect("duplicate values", c, 2, 6, 0, 1);
    const int d[] = {3, 2, 3};              expect("same value, one pair", d, 3, 6, 0, 2);
    const int e[] = {-1, -2, -3, -4};       expect("negatives", e, 4, -6, 1, 3);
    const int f[] = {0, 0};                 expect("zero target and zeros", f, 2, 0, 0, 1);
    const int g[] = {1000000000, 1000000000};
    expect("overflow guard", g, 2, 2000000000LL, 0, 1);
    const int h[] = {1, 5, 2, 7, 3};        expect("answer in the middle", h, 5, 9, 2, 3);

    /* input is not modified (invariant 3) */
    int orig[] = {3, 2, 4, 1}, copy[4];
    memcpy(copy, orig, sizeof orig);
    int i, j; two_sum(orig, 4, 4, &i, &j);
    assert(memcmp(orig, copy, sizeof orig) == 0);
    printf("  PASS %-26s\n", "input not modified"); checks++;

    /* no pair: pinned, because the spec leaves it unspecified */
    const int k[] = {1, 2, 3};
    assert(two_sum(k, 3, 100, &i, &j) == 0);
    printf("  PASS %-26s\n", "no pair returns 0"); checks++;

    /* defensive: the contract says these must not crash */
    assert(two_sum(NULL, 2, 3, &i, &j) == 0);
    assert(two_sum(a, 1, 3, &i, &j) == 0);
    printf("  PASS %-26s\n", "null and n<2 refused"); checks++;

    /* many collisions: 2000 consecutive keys stress the probe sequence */
    static int big[2000];
    for (int x = 0; x < 2000; x++) big[x] = x;
    expect("2000 keys, probing", big, 2000, 1999 + 1998, 1998, 1999);

    printf("\n  %d checks passed\n", checks);
    return 0;
}
