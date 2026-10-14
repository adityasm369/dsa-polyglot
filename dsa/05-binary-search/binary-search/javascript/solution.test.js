'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const { search, searchCounting } = require('./solution');

const INT_MIN = -(2 ** 31), INT_MAX = 2 ** 31 - 1;
const CASES = [
  ['empty array', [], 5, -1],
  ['one element present', [5], 5, 0],
  ['one element absent', [5], 3, -1],
  ['target is first', [1, 2, 3, 4, 5], 1, 0],
  ['target is last', [1, 2, 3, 4, 5], 5, 4],
  ['absent below range', [1, 2, 3], 0, -1],
  ['absent above range', [1, 2, 3], 9, -1],
  ['absent in a gap', [1, 3, 5, 7], 4, -1],
  ['two elements', [1, 2], 2, 1],
  ['negatives', [-5, -3, -1], -3, 1],
  ['extreme values', [INT_MIN, 0, INT_MAX], INT_MAX, 2],
  ['extreme low', [INT_MIN, 0, INT_MAX], INT_MIN, 0],
];
for (const [name, nums, target, want] of CASES) {
  test(name, () => {
    const before = [...nums];
    const got = search(nums, target);
    assert.equal(got, want);
    if (got !== -1) assert.equal(nums[got], target);
    assert.deepEqual(nums, before, 'input not modified');
  });
}
test('non-array returns -1', () => assert.equal(search(null, 1), -1));

const big = Array.from({ length: 10000 }, (_, i) => i * 2);
test('10k: every index findable, every gap rejected', () => {
  for (let i = 0; i < big.length; i++) {
    assert.equal(search(big, i * 2), i);
    assert.equal(search(big, i * 2 + 1), -1);
  }
});
test('is logarithmic', () => {
  const limit = Math.ceil(Math.log2(big.length + 1));
  for (const v of [big[0], big[5000], big[9999]]) {
    assert.ok(searchCounting(big, v)[1] <= limit);
  }
});
test('terminates for every target on every small array', () => {
  for (let n = 0; n < 12; n++) {
    const a = Array.from({ length: n }, (_, i) => i);
    for (let t = -2; t < n + 3; t++) search(a, t);
  }
});
test('doubles cannot overflow at array scale', () => {
  // The JDK bug cannot occur here: 2^32 is far below 2^53.
  const lo = 2 ** 31, hi = 2 ** 31 + 2;
  assert.equal((lo + hi) / 2, lo + (hi - lo) / 2, 'both forms agree in JS');
  assert.ok(Number.isSafeInteger(lo + hi));
});
