'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const { climbStairs } = require('./solution');

for (const [n, want] of [[1, 1], [2, 2], [3, 3], [4, 5], [5, 8], [10, 89], [45, 1836311903]]) {
  test(`n=${n}`, () => assert.equal(climbStairs(n), want));
}
test('every n in 1..45 is positive', () => {
  for (let n = 1; n <= 45; n++) assert.ok(climbStairs(n) > 0);
});
test('exact up to the spec limit (below 2^53)', () => {
  assert.ok(Number.isSafeInteger(climbStairs(45)));
});
