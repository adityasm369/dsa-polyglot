#include "solution.h"
#include <assert.h>
#include <stdio.h>

static int checks = 0;
static void expect(int n, long long want) {
    long long got = climb_stairs(n);
    if (got != want) { printf("  FAIL n=%d got %lld want %lld\n", n, got, want); assert(0); }
    printf("  PASS n=%-3d %lld\n", n, got);
    checks++;
}

int main(void) {
    expect(1, 1);
    expect(2, 2);
    expect(3, 3);
    expect(4, 5);
    expect(5, 8);
    expect(10, 89);
    expect(45, 1836311903LL);      /* the largest allowed input */
    for (int n = 1; n <= 45; n++) assert(climb_stairs(n) > 0);   /* invariant 2 */
    printf("  PASS every n in 1..45 is positive\n"); checks++;
    printf("\n  %d checks passed\n", checks);
    return 0;
}
