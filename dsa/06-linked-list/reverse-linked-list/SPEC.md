# reverse-linked-list

- **Pattern:** 06 — linked lists
- **Difficulty:** basic
- **Written:** before any code in this folder

## Problem

Given the head of a singly linked list, reverse the list and return the new
head.

## Contract

```
input   head: a node, or empty (no list)
        each node holds an int value and a pointer/reference to the next node;
        the last node points to nothing
output  the head of the reversed list
        the same nodes, with each next pointer flipped
```

The function **reverses in place**. It reuses the existing nodes; it does not
copy them. That is the point of the problem, and the tests check it by
inspecting the original head afterwards.

## Constraints

```
0 <= number of nodes <= 5000
-5000 <= Node.val <= 5000
```

The 5000 is small on purpose: it is not what makes a recursive version unsafe.
The tests exercise 100 000 nodes, because that is where recursion's stack
depth becomes a real defect and not a theoretical one.

## Invariants

1. **Every node survives.** Nothing is lost and nothing is duplicated. The
   number of nodes before and after is the same.
2. **After reversal the original head is the tail.** Its `next` is empty. This
   follows from invariant 1, and every test checks it: a student who forgets to
   terminate the list gets a cycle or a truncated result, and this is how they
   learn which.
3. Reversing twice returns the original order.
4. Extra space is **O(1)**: the algorithm needs three pointers, no matter how
   long the list is.

## Complexity target

| | time | space | |
|---|---|---|---|
| copy into an array, then rebuild | O(n) | O(n) | correct, and wastes the point |
| recursive | O(n) | **O(n)** | each call is a stack frame; overflows on long lists |
| **required: iterative, three pointers** | **O(n)** | **O(1)** | |

## The three pointers

```
prev = nothing,  cur = head

  while cur is not nothing:
      save the rest of the list before we break it
      point cur back at prev
      step prev forward to cur, and cur forward to the saved rest

  return prev
```

The one thing students forget is the first step: **save `next` before rewriting
`next`**. Without it the rest of the list is lost the moment the pointer flips,
and the loop ends after one node. Every failing submission in this problem is
that mistake.

## Edge cases the tests must cover

| case | input | expected | what it breaks |
|---|---|---|---|
| empty | no nodes | empty | dereferencing a null head |
| one node | `[1]` | `[1]` | loops that assume at least two |
| two nodes | `[1, 2]` | `[2, 1]` | the smallest case where the flip matters |
| odd length | `[1, 2, 3]` | `[3, 2, 1]` | — |
| negatives and zero | `[-1, 0, 1]` | `[1, 0, -1]` | — |
| long list | 100 000 nodes | reversed | **recursion overflows the stack in C and Java** |
| twice | reverse of reverse | original | proves the flips compose |

## Teaching notes

1. Draw it. Three boxes, arrows, and a student moving them. The pointer
   surgery is only confusing if it is described rather than drawn.
2. Ask them to write the **recursive** version first, because it is the one
   everyone can reason about. Then run the 100 000-node test. Java throws
   `StackOverflowError`. C segfaults. Python raises `RecursionError` at its
   default limit of 1000. That is the moment "elegant" and "safe" part ways.
3. Then show the iterative version and ask what the three pointers are doing.
   Each one answers a question: where is the rest, where is the reversed part,
   where am I.
4. Open the Rust version last. Ask how the compiler knows the old node is no
   longer used, and why the C version has no such guarantee.

## Common mistakes

- Flipping `next` before saving it — loses the rest of the list.
- Returning `head` instead of `prev`. `head` is the old first node, which is now
  the last one.
- Forgetting to set the old head's `next` to empty. Usually the old head then
  points at a node that points back to it, and the list has a cycle.
- In C, leaking nodes by overwriting the only pointer to a node before freeing
  it. The sanitiser reports this; do not skip it.
- Recursing. Correct on short lists, a crash on long ones.
