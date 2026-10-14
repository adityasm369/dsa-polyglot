# 01 — Arrays and hashing

## The idea in one line

Trade memory for time: remember what you have already seen, so you never look
at it twice.

## How to recognise it

You are about to write a nested loop over the same array, and the inner loop is
only asking *"have I seen something before?"* or *"how many times?"*. That
question is answered by a hash table in O(1), which collapses O(n²) to O(n).

Signals in a problem statement:

- "find two elements such that …"
- "contains a duplicate"
- "the most frequent / first unique"
- "are these two inputs anagrams / permutations"
- "group the ones that …"

## What it costs

| | time | space |
|---|---|---|
| nested loop | O(n²) | O(1) |
| hash table | O(n) **average** | O(n) |

Say **average** out loud when teaching. A hash table is O(1) *expected*, not
guaranteed: with adversarial keys every insert can collide and degrade to O(n)
per operation. This is not academic — it was a real denial-of-service class
(hash flooding) against PHP, Java, Python and Ruby web servers in 2011, fixed
by randomising hash seeds. Ask your students what the worst case of their
`unordered_map` is and why Java's `HashMap` switches a long bucket chain to a
balanced tree.

## What the seven languages show here

This pattern is the sharpest available demonstration of what a standard library
is worth, which is why it is problem one.

| language | the hash table you get |
|---|---|
| Python | `dict`, `collections.Counter` — built into the syntax |
| Java | `HashMap`, autoboxes `int` to `Integer` (a real cost) |
| C++ | `unordered_map`, `map` if you want ordering and O(log n) |
| JavaScript | `Map`, or an object; `Map` keeps insertion order and takes any key |
| Go | `map[int]int`, with the two-value comma-ok idiom for "is it there" |
| Rust | `HashMap`, and the compiler makes you handle "not found" |
| **C** | **nothing — you write it** |

The C solution in this folder implements open addressing with linear probing,
in about 60 lines. That is the lesson: every other row in that table is this
file, written once by someone else.

## Problems in this pattern

| | problem | difficulty | why it is here |
|---|---|---|---|
| 1 | [two-sum](two-sum/) | basic | the pattern in its smallest form |
| 2 | group-anagrams | medium | hashing a *derived* key, not the value |
| 3 | longest-consecutive-sequence | hard | a set turns a sort into a scan |
