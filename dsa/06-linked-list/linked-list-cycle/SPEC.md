# linked-list-cycle

- **Pattern:** 06 — linked lists
- **Difficulty:** medium
- **Written:** before any code in this folder

## Problem

Given the head of a linked list, return true if the list contains a cycle — some
node's `next` leads back to a node already visited — and false otherwise.

## Contract

```
input   head: a node, or empty; the list may or may not loop back
output  true if following `next` from head eventually revisits a node
```

## Constraints

```
0 <= number of nodes <= 10^4
-10^5 <= Node.val <= 10^5
```

The function does not need to find where the cycle starts, and must not modify
the list.

## Invariants

1. The function **terminates on every input**, including the cyclic ones. An
   implementation that walks a cycle forever has not answered the question.
2. The list is **not modified**: no node is relinked, no flag is written into a
   node. (A common shortcut marks visited nodes. It works, and it is forbidden
   here because it destroys the data it inspects.)
3. Extra space is **O(1)**.

## Complexity target

| | time | space | |
|---|---|---|---|
| remember every visited node in a set | O(n) | O(n) | correct and obvious |
| mark nodes visited by editing them | O(n) | O(1) | forbidden by invariant 2 |
| **required: Floyd's tortoise and hare** | **O(n)** | **O(1)** | two pointers at different speeds |

## Why two speeds works

Move a slow pointer one step and a fast pointer two steps each round.

- If the list ends, the fast pointer reaches nothing and the answer is false.
- If there is a cycle, the fast pointer enters it first. The gap between the two
  pointers then shrinks by one each round, so they must meet inside the cycle.

The gap argument is the whole proof. Ask students to state it before they code
it. Every other reasoning error in this problem is a loss of that argument.

## Edge cases the tests must cover

| case | input | expected | what it breaks |
|---|---|---|---|
| empty | no nodes | false | dereferencing a null head |
| one node, no cycle | `[1]` | false | `fast.next.next` on a one-node list |
| two nodes, no cycle | `[1,2]` | false | fast moves past the end |
| one node, points at itself | `[1]` → self | true | the smallest cycle |
| cycle back to head | `[1,2,3]`, tail → head | true | — |
| cycle to middle | `[1,2,3,4]`, tail → node 2 | true | — |
| long, no cycle | 10 000 nodes | false | — |
| long, cycle at the end | 10 000 nodes, tail → head | true | the time bound |

## Teaching notes

1. Ask for the hash-set version first. It is correct, and most students will
   reach for it. Ask what it costs in memory on a 10⁴-node list, then on a
   10⁸-node list.
2. Then ask whether the list can be checked without remembering anything. The
   tortoise and hare appears as the answer to a question, not as a trick.
3. Draw the gap argument on a whiteboard with a six-node cycle. Watch the gap
   close.
4. Show the Rust version last: `Option<Box<Node>>` cannot form a cycle at all, so
   the Rust test uses a raw-index arena to build one. That is an honest
   difference in what the language allows.

## Common mistakes

- Checking `fast == slow` before advancing, so they are equal at the start and
  the function returns true for every list.
- `while (fast)` instead of `while (fast && fast.next)`, which crashes on a list
  with an even number of nodes.
- Using `==` on values rather than on node identity. Two nodes can hold the same
  value and be different nodes.
- Marking nodes visited by setting `val` to a sentinel — violates invariant 2.
