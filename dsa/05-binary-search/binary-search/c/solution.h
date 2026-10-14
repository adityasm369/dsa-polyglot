#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H
#include <stddef.h>
/* Index of target in the ascending, duplicate-free nums, or -1.
 * Returns ptrdiff_t, not int: an index must be able to address the whole array
 * on a 64-bit machine, and that is exactly the case the JDK bug lived in. */
ptrdiff_t bsearch_index(const int *nums, size_t n, int target);
ptrdiff_t bsearch_counting(const int *nums, size_t n, int target, int *steps);
#endif
