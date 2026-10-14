'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const { isPalindrome } = require('./solution');

const CASES = [
  ['empty', '', true], ['one character', 'a', true], ['only punctuation', '.,!', true],
  ['mixed case', 'Aa', true], ['digits count', '0P', false],
  ['the textbook one', 'A man, a plan, a canal: Panama', true],
  ['nearly', 'race a car', false], ['all skipped but one', '...a...', true],
  ['spaces only', '   ', true], ['digits palindrome', '12321', true],
  ['digits not', '12345', false],
];
for (const [name, s, want] of CASES) {
  test(name, () => assert.equal(isPalindrome(s), want));
}
test('non-string is accepted', () => assert.equal(isPalindrome(null), true));
test('200k characters', () => assert.equal(isPalindrome('a'.repeat(200000)), true));
test('input is immutable anyway', () => {
  const s = 'A man, a plan';
  isPalindrome(s);
  assert.equal(s, 'A man, a plan');   // JS strings cannot be mutated at all
});
