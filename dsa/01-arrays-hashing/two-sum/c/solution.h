#ifndef TWO_SUM_H
#define TWO_SUM_H
#include <stddef.h>
/* Writes the two indices and returns 1, or returns 0 if no pair exists.
 * `nums` is not modified. `target` is long long because the sum overflows
 * int32 at the limits SPEC.md allows. */
int two_sum(const int *nums, size_t n, long long target, int *out_i, int *out_j);
#endif
