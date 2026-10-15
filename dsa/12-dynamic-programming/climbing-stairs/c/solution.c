/* climbing-stairs. Time O(n), Space O(1).
 *
 * long long, not int: the answer for n = 45 fits in int32, but the spec allows
 * the function to be generalised, and a student who writes `int` here has
 * written a bug that waits for n = 47. Return type and accumulator are wide.
 */
#include "solution.h"

long long climb_stairs(int n) {
    if (n <= 2) return n < 1 ? 0 : n;   /* ways(1)=1, ways(2)=2 */
    long long prev = 1, cur = 2;
    for (int i = 3; i <= n; i++) {
        long long next = prev + cur;     /* the last move was a 1 or a 2 */
        prev = cur;
        cur = next;
    }
    return cur;
}
