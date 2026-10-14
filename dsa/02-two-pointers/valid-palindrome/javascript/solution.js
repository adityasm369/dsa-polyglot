'use strict';
/**
 * valid-palindrome. Time O(n), Space O(1).
 *
 * JavaScript strings are UTF-16, so s[i] is a 16-bit code UNIT, not a
 * character. For the ASCII the spec allows they coincide; for anything above
 * U+FFFF (emoji, some CJK) one character occupies two units and s[i] returns
 * half of it. Go and Java have the same problem in different clothes. Only
 * Python and Rust are honest about it -- Python by indexing code points, Rust
 * by refusing to index at all.
 *
 * @param {string} s
 * @returns {boolean}
 */
function isPalindrome(s) {
  if (typeof s !== 'string' || s.length === 0) return true;
  let i = 0, j = s.length - 1;
  const alnum = (c) => /[a-z0-9]/i.test(c);
  while (i < j) {
    while (i < j && !alnum(s[i])) i++;
    while (i < j && !alnum(s[j])) j--;
    if (s[i].toLowerCase() !== s[j].toLowerCase()) return false;
    i++; j--;
  }
  return true;
}
module.exports = { isPalindrome };
