'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const { hasCycle } = require('./solution');

const build = (...values) => {
  const ns = values.map((val) => ({ val, next: null }));
  for (let i = 0; i + 1 < ns.length; i++) ns[i].next = ns[i + 1];
  return ns;
};

test('empty', () => assert.equal(hasCycle(null), false));
test('one node, no cycle', () => assert.equal(hasCycle(build(1)[0]), false));
test('two nodes, no cycle', () => assert.equal(hasCycle(build(1, 2)[0]), false));
test('one node, self-loop', () => {
  const [n] = build(1);
  n.next = n;
  assert.equal(hasCycle(n), true);
});
test('cycle back to head', () => {
  const ns = build(1, 2, 3);
  ns[2].next = ns[0];
  assert.equal(hasCycle(ns[0]), true);
});
test('cycle to middle', () => {
  const ns = build(1, 2, 3, 4);
  ns[3].next = ns[1];
  assert.equal(hasCycle(ns[0]), true);
});
test('equal values, distinct nodes: identity not value', () => {
  assert.equal(hasCycle(build(7, 7, 7, 7)[0]), false);
});
test('10,000 nodes, no cycle', () => {
  assert.equal(hasCycle(build(...Array.from({ length: 10000 }, (_, i) => i))[0]), false);
});
test('10,000 nodes, cycle at end', () => {
  const ns = build(...Array.from({ length: 10000 }, (_, i) => i));
  ns[ns.length - 1].next = ns[0];
  assert.equal(hasCycle(ns[0]), true);
});
