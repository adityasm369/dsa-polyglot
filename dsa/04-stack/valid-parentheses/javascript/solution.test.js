'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const { isValid } = require('./solution');

const CASES = [
  ['single opener', '(', false], ['single closer', ')', false],
  ['simple', '()', true], ['all three types', '()[]{}', true],
  ['nested', '([{}])', true], ['interleaved', '([)]', false],
  ['closes too early', ')(', false], ['left open', '(((', false],
  ['empty string', '', true], ['non-string', null, false],
];
for (const [name, s, want] of CASES) test(name, () => assert.equal(isValid(s), want));
test('long balanced', () => assert.equal(isValid('('.repeat(5000) + ')'.repeat(5000)), true));
test('input unchanged', () => {
  const s = '([{}])';
  isValid(s);
  assert.equal(s, '([{}])');
});
