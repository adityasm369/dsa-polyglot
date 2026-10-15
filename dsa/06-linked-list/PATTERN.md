# 06 — Linked lists

## The idea in one line

A list is a chain of nodes, each pointing at the next. Moving through it is
easy; changing it is where the bugs live, because every pointer you rewrite is
a pointer something else may still be using.

## How to recognise it

- "reverse", "reorder", "remove the nth from the end"
- "detect a cycle"
- "merge two sorted lists"
- The input is a head pointer and nothing else — no index, no length.

## What it costs

| operation | array | linked list |
|---|---|---|
| access the i-th element | O(1) | O(n) |
| insert or delete at a known node | O(n) shift | O(1) |
| memory | one block | one allocation per node |

The second row is why linked lists exist, and the third row is why they are
slow in practice: each node is a separate allocation, so traversal chases
pointers across memory. A Java `LinkedList` of a million integers is a million
heap objects; `ArrayList` is one array. Ask students which they would expect to
iterate faster, then time it.

## Why this pattern is the best polyglot lesson in the course

Reversing a list in place is four lines of pointer surgery, and it forces one
question onto every language: **who owns the nodes?**

| language | who frees a node |
|---|---|
| C | you, with `free`, and only once |
| C++ | you, or a smart pointer; the destructor runs at scope end |
| Java | the garbage collector, whenever it likes |
| Python | reference counting plus a cycle collector |
| Go | the garbage collector |
| Rust | the compiler, at a point it can prove statically |

In Rust the in-place reversal is a `while let` loop that moves `Option<Box<Node>>`
values around. The borrow checker will not let you keep two references to the
same node, which is precisely the situation a naive reversal creates and then
mishandles. Students who have written the C version understand *why* the Rust
version is shaped the way it is.

## Problems in this pattern

| | problem | difficulty | why it is here |
|---|---|---|---|
| 1 | [reverse-linked-list](reverse-linked-list/) | basic | the pointer surgery, and the ownership question in seven forms |
