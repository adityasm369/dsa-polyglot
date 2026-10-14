'use strict';
/**
 * binary-search. Time O(log n), Space O(1).
 *
 * JavaScript numbers are IEEE-754 doubles, exact for integers up to 2^53. An
 * array cannot have more than 2^32-1 elements, so (lo + hi) / 2 can never
 * overflow here -- JavaScript is structurally immune to the JDK bug. Math.floor
 * is still required, because / is real division and would give a fractional
 * index.
 *
 * @param {number[]} nums  ascending, no duplicates
 * @param {number} target
 * @returns {number} index, or -1
 */
function search(nums, target) {
  if (!Array.isArray(nums) || nums.length === 0) return -1;
  let lo = 0, hi = nums.length - 1;
  while (lo <= hi) {
    // The safe form regardless -- the habit is what transfers to Java and C.
    const mid = lo + Math.floor((hi - lo) / 2);
    if (nums[mid] === target) return mid;
    if (nums[mid] < target) lo = mid + 1;
    else hi = mid - 1;
  }
  return -1;
}

/** Index and iteration count, for the O(log n) teaching note. */
function searchCounting(nums, target) {
  let steps = 0;
  if (!Array.isArray(nums) || nums.length === 0) return [-1, 0];
  let lo = 0, hi = nums.length - 1;
  while (lo <= hi) {
    steps++;
    const mid = lo + Math.floor((hi - lo) / 2);
    if (nums[mid] === target) return [mid, steps];
    if (nums[mid] < target) lo = mid + 1;
    else hi = mid - 1;
  }
  return [-1, steps];
}
module.exports = { search, searchCounting };
