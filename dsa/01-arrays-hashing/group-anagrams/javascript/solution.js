'use strict';
/**
 * group-anagrams. Time O(n*k), Space O(n*k).
 *
 * The key is a joined string, not an array. A Map compares object keys by
 * identity, so an array key can never be looked up with a fresh array:
 *   new Map().set([1, 2], 'x').get([1, 2])  // undefined
 * Both literals are distinct objects. Students should predict that line before
 * running it. See solution.test.js, which asserts it.
 *
 * @param {string[]} strs
 * @returns {string[][]}
 */
function groupAnagrams(strs) {
  const index = new Map();      // key -> position in out
  const out = [];
  if (!Array.isArray(strs)) return out;

  for (const s of strs) {
    const counts = new Array(26).fill(0);
    for (const ch of s) {
      const i = ch.charCodeAt(0) - 97;
      if (i >= 0 && i < 26) counts[i]++;
    }
    const key = counts.join('#');   // '#' so [1,11] and [11,1] differ
    if (index.has(key)) {
      out[index.get(key)].push(s);
    } else {
      index.set(key, out.length);
      out.push([s]);
    }
  }
  return out;
}
module.exports = { groupAnagrams };
