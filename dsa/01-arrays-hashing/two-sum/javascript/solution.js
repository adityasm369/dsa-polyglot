'use strict';
/**
 * two-sum. Time O(n) average, Space O(n).
 *
 * Map, not a plain object. Three reasons a fourth-year should know:
 *   1. object keys are coerced to strings, so 1 and '1' collide;
 *   2. an object inherits keys like 'constructor' and '__proto__';
 *   3. Map.has() answers "is it there", where `if (obj[k])` answers
 *      "is it truthy" -- and index 0 is falsy. SPEC.md's [0,0] case fails on
 *      exactly that mistake.
 *
 * Numbers are IEEE-754 doubles: integers are exact to 2^53, so the 2e9 sums in
 * the spec cannot overflow. They would silently lose precision past 9e15,
 * which is JavaScript's version of the C overflow problem.
 *
 * @param {number[]} nums
 * @param {number} target
 * @returns {[number, number] | null}
 */
function twoSum(nums, target) {
  if (!Array.isArray(nums) || nums.length < 2) return null;
  const seen = new Map();                 // value -> first index
  for (let j = 0; j < nums.length; j++) {
    const want = target - nums[j];
    if (seen.has(want)) return [seen.get(want), j];
    if (!seen.has(nums[j])) seen.set(nums[j], j);   // first index wins
  }
  return null;
}
module.exports = { twoSum };
