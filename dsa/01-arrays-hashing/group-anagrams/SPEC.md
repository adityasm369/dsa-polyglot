# group-anagrams

- **Pattern:** 01 — arrays and hashing
- **Difficulty:** medium
- **Written:** before any code in this folder

## Problem

Given an array of strings, group the anagrams together. Two strings are anagrams
if one is a rearrangement of the other's letters. Return the groups in any order,
and the strings within each group in any order.

## Contract

```
input   strs: array of strings, lowercase a-z only
output  a partition of the indices of strs into groups; each group holds exactly
        the strings that are anagrams of one another
```

## Constraints

```
1 <= len(strs) <= 10^4
0 <= len(strs[i]) <= 100
strs[i] consists of lowercase English letters only
```

The empty string is an anagram of itself and nothing else, so `""` forms its
own group.

## Invariants

1. **Each string appears in exactly one group.** A string dropped or duplicated
   is a wrong answer even if every group looks right.
2. **Two strings share a group if and only if they are anagrams.** Both
   directions: a group that merges two non-anagrams is as wrong as a split pair.
3. The input is **not modified**.

## The key is the whole problem

Anagrams have the same letters with the same counts. So any canonical
representation of those counts is a valid key for a hash map:

| key | build cost per string of length k | notes |
|---|---|---|
| the string sorted | O(k log k) | simplest; the common first answer |
| the 26 letter counts | O(k) | **required**, and it is the one that names the principle |

The count key is the more instructive one: it shows that a grouping problem is
really a question about **what the equivalence class is**, and the answer
("same multiset of letters") is a fact about the data rather than about the
method.

## Complexity target

| | time | space |
|---|---|---|
| compare every pair | O(n² · k) | O(1) extra |
| sorted-string key in a map | O(n · k log k) | O(n · k) |
| **required: count key in a map** | **O(n · k)** | **O(n · k)** |

## What the seven languages show here

Hashing an array is the one thing a standard library gives you almost for free,
which makes it the cleanest place to see what that library is worth:

| language | the map | the key |
|---|---|---|
| Python | `dict` with a `tuple` key | tuples hash by value |
| Java | `HashMap<String, List<String>>` | `String` hashes by value |
| C++ | `unordered_map<string, vector<string>>` | likewise |
| JavaScript | `Map` keyed by a joined string | a `Map` key of an array is compared by identity — a real trap |
| Go | `map[[26]int][]string` | an **array** is comparable and hashable; a slice is not |
| Rust | `HashMap<[u8; 26], Vec<String>>` | arrays implement `Hash` |
| **C** | **none — the solution writes a small open-addressing table** | |

The JavaScript row is the sharpest: `new Map().set([1,2], 'x').get([1,2])` is
`undefined`, because the two array literals are different objects. Ask students
to predict it before they run it.

## Edge cases the tests must cover

| case | input | expected groups | what it breaks |
|---|---|---|---|
| single string | `["a"]` | `[["a"]]` | — |
| empty string | `[""]` | `[[""]]` | a key that cannot be built for length 0 |
| all empty | `["", ""]` | one group of two | — |
| no anagrams | `["abc","def"]` | two groups | merging everything into one |
| classic | `["eat","tea","tan","ate","nat","bat"]` | 3 groups | — |
| same letters, different counts | `["aab","abb"]` | two groups | **a key that ignores counts** — e.g. a set of letters |
| repeated string | `["ab","ab"]` | one group of two | duplicates dropped by a set |

## Teaching notes

1. Give them `["aab","abb"]` first. Ask what key they would use. Many propose
   the set of letters. That is the counting trap, and it is the invariant 2
   failure in one line.
2. Ask them to write the sorted-key version and then predict its cost for
   strings of length 100. Then ask whether counting can be done without sorting.
3. Show the JavaScript `Map` with array keys. Then the Go version with `[26]int`,
   where the same idea works because arrays are values.

## Common mistakes

- A key that is the set of letters rather than the multiset.
- Building the key from a mutable structure and then using it after mutation.
- JavaScript: using an array as a `Map` key (identity, not value).
- Go: using `[]int` as a map key — slices are not comparable and do not compile.
- Forgetting that `""` is a valid key.
