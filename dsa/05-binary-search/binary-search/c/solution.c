/* binary-search. Time O(log n), Space O(1).
 *
 * In C, signed integer overflow is UNDEFINED BEHAVIOUR -- not wraparound. The
 * compiler is entitled to assume it never happens, which means a later
 * `if (mid < 0)` check can be deleted as provably-false. So (lo + hi) / 2 is
 * not merely risky here, it is unfixable-after-the-fact.
 *
 * Indices are size_t / ptrdiff_t so the function can address a real array on a
 * 64-bit host. That is the case Bloch found broken in java.util.Arrays.
 */
#include "solution.h"

ptrdiff_t bsearch_index(const int *nums, size_t n, int target) {
    if (!nums || n == 0) return -1;
    size_t lo = 0, hi = n - 1;
    for (;;) {
        /* lo + (hi - lo) / 2. hi >= lo always holds here, so (hi - lo) cannot
         * underflow, and the sum cannot exceed hi -- no overflow is possible
         * for any n that fits in memory. */
        size_t mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return (ptrdiff_t)mid;
        if (nums[mid] < target) {
            /* Unsigned indices need care the signed version does not: there is
             * no -1 to fall back on, so the "ran off the end" case must be
             * tested before the increment rather than after. */
            if (mid == hi) return -1;
            lo = mid + 1;
        } else {
            if (mid == lo) return -1;
            hi = mid - 1;
        }
    }
}

ptrdiff_t bsearch_counting(const int *nums, size_t n, int target, int *steps) {
    *steps = 0;
    if (!nums || n == 0) return -1;
    size_t lo = 0, hi = n - 1;
    for (;;) {
        (*steps)++;
        size_t mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return (ptrdiff_t)mid;
        if (nums[mid] < target) { if (mid == hi) return -1; lo = mid + 1; }
        else                    { if (mid == lo) return -1; hi = mid - 1; }
    }
}
