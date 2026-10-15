'use strict';
/**
 * climbing-stairs. Time O(n), Space O(1).
 *
 * Numbers are doubles, exact to 2^53. The answer for n = 78 is the first that
 * exceeds 2^53, so for larger n this returns a value that is no longer exact.
 * The spec stops at 45, far below that, and the test says so explicitly.
 * BigInt would be the fix past it.
 *
 * @param {number} n
 * @returns {number}
 */
function climbStairs(n) {
  if (n <= 2) return n < 1 ? 0 : n;
  let prev = 1, cur = 2;
  for (let i = 3; i <= n; i++) {
    const next = prev + cur;
    prev = cur;
    cur = next;
  }
  return cur;
}
module.exports = { climbStairs };
