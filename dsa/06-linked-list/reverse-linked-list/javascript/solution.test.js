'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const { reverseList, ListNode } = require('./solution');

const build = (values) => values.reduceRight((next, val) => new ListNode(val, next), null);
const collect = (head) => {
  const out = [];
  for (let n = head; n !== null; n = n.next) out.push(n.val);
  return out;
};

const CASES = [
  ['empty', [], []],
  ['one node', [1], [1]],
  ['two nodes', [1, 2], [2, 1]],
  ['odd length', [1, 2, 3], [3, 2, 1]],
  ['negatives and zero', [-1, 0, 1], [1, 0, -1]],
];
for (const [name, values, want] of CASES) {
  test(name, () => assert.deepEqual(collect(reverseList(build(values))), want));
}
test('original head is now the tail (invariant 2)', () => {
  const head = build([1, 2, 3]);
  reverseList(head);
  assert.equal(head.next, null);
});
test('reverse twice is identity', () => {
  const v = [4, 1, 3, 2];
  assert.deepEqual(collect(reverseList(reverseList(build(v)))), v);
});
test('every node survives (invariant 1)', () => {
  assert.equal(collect(reverseList(build(Array.from({ length: 1000 }, (_, i) => i)))).length, 1000);
});
test('100,000 nodes, iteratively', () => {
  const v = Array.from({ length: 100000 }, (_, i) => i);
  assert.equal(collect(reverseList(build(v)))[0], 99999);
});
