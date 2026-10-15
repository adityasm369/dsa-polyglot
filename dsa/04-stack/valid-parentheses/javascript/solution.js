'use strict';
/**
 * valid-parentheses. Time O(n), Space O(n).
 *
 * An array is the stack: push and pop are O(1) amortised. Note that
 * stack[stack.length - 1] is undefined on an empty array rather than an error,
 * so the empty check is still required before a comparison.
 *
 * @param {string} s
 * @returns {boolean}
 */
const OPEN_FOR = { ')': '(', ']': '[', '}': '{' };

function isValid(s) {
  if (typeof s !== 'string') return false;
  const stack = [];
  for (const c of s) {
    if (c in OPEN_FOR) {                        // closer
      if (stack.length === 0 || stack.pop() !== OPEN_FOR[c]) return false;
    } else if (c === '(' || c === '[' || c === '{') {
      stack.push(c);
    } else {
      return false;                             // outside the spec
    }
  }
  return stack.length === 0;
}
module.exports = { isValid };
