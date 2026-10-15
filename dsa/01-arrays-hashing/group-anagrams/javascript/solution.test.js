'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const { groupAnagrams } = require('./solution');

const isAnagram = (a, b) =>
  [...a].sort().join('') === [...b].sort().join('');

function checkPartition(strs, wantGroups) {
  const groups = groupAnagrams(strs);
  assert.equal(groups.length, wantGroups, 'group count');
  // Invariant 1: every string appears exactly once.
  assert.deepEqual([...groups.flat()].sort(), [...strs].sort());
  // Invariant 2, both directions.
  groups.forEach((g, gi) => {
    for (const a of g) {
      for (const b of g) assert.ok(isAnagram(a, b), `${a}/${b} merged wrongly`);
      groups.forEach((h, gj) => {
        if (gi === gj) return;
        for (const b of h) assert.ok(!isAnagram(a, b), `${a}/${b} split wrongly`);
      });
    }
  });
}

const CASES = [
  ['single string', ['a'], 1],
  ['empty string', [''], 1],
  ['all empty', ['', ''], 1],
  ['no anagrams', ['abc', 'def'], 2],
  ['classic', ['eat', 'tea', 'tan', 'ate', 'nat', 'bat'], 3],
  ['same letters diff counts', ['aab', 'abb'], 2],
  ['repeated string', ['ab', 'ab'], 1],
  ['empty mixed in', ['eat', 'tea', 'tan', 'ate', 'nat', 'bat', '', 'aab'], 5],
];
for (const [name, strs, want] of CASES) test(name, () => checkPartition(strs, want));

test('non-array input', () => assert.deepEqual(groupAnagrams(null), []));

test('a Map compares array keys by identity, not value', () => {
  const m = new Map();
  m.set([1, 2], 'x');
  assert.equal(m.get([1, 2]), undefined);   // the trap this solution avoids
  const sameRef = [1, 2];
  m.set(sameRef, 'y');
  assert.equal(m.get(sameRef), 'y');        // only the same object works
});

test('the # separator keeps [1,11] and [11,1] apart', () => {
  const groups = groupAnagrams(['a' + 'b'.repeat(11), 'a'.repeat(11) + 'b']);
  assert.equal(groups.length, 2);
});

test('input not modified', () => {
  const strs = ['eat', 'tea'];
  groupAnagrams(strs);
  assert.deepEqual(strs, ['eat', 'tea']);
});
