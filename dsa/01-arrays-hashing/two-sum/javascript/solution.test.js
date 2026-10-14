'use strict';
// node --test test_solution.js   (the runner is built in since Node 18)
const test = require('node:test');
const assert = require('node:assert/strict');
const { twoSum } = require('./solution');

const CASES = [
  ['minimum size',          [1, 2],                   3,    [0, 1]],
  ['answer at the ends',     [3, 2, 4, 1],            4,    [0, 3]],
  ['duplicate values',       [3, 3],                  6,    [0, 1]],
  ['same value, one pair',   [3, 2, 3],               6,    [0, 2]],
  ['negatives',              [-1, -2, -3, -4],       -6,    [1, 3]],
  ['zero target and zeros',  [0, 0],                  0,    [0, 1]],
  ['overflow guard',         [1e9, 1e9],              2e9,  [0, 1]],
  ['answer in the middle',   [1, 5, 2, 7, 3],         9,    [2, 3]],
];

for (const [name, nums, target, want] of CASES) {
  test(name, () => {
    const input = [...nums];
    const got = twoSum(input, target);
    assert.deepEqual(got, want);
    assert.ok(got[0] < got[1], 'indices ordered');
    assert.equal(input[got[0]] + input[got[1]], target);
    assert.deepEqual(input, nums, 'input not modified');
  });
}

test('no pair returns null', () => assert.equal(twoSum([1, 2, 3], 100), null));
test('n<2 returns null', () => assert.equal(twoSum([1], 1), null));
test('non-array returns null', () => assert.equal(twoSum(null, 1), null));
test('the falsy-zero trap', () => {
  // `if (map[0])` would be false here and the pair would be missed.
  assert.deepEqual(twoSum([0, 0], 0), [0, 1]);
  assert.deepEqual(twoSum([0, 4], 4), [0, 1]);
});
test('2000 keys', () => assert.deepEqual(twoSum([...Array(2000).keys()], 3997), [1998, 1999]));
