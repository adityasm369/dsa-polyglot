# 04 — Stack

## The idea in one line

Last in, first out. The most recent unresolved thing is always the one you need
next.

## How to recognise it

Nested or matched structure, where each opener must be closed by the most
recent unclosed opener: brackets, tags, function calls, undo history, the
call stack itself.

Signals:
- "valid parentheses / balanced brackets"
- "the next greater element"
- "evaluate an expression"
- "undo", "backtrack", "nested"

## What it costs

| operation | time | space |
|---|---|---|
| push, pop, peek | O(1) | — |
| the whole algorithm | O(n) | O(n) worst case |

## The language difference that matters here

The same data structure is a `list` in Python, a `Stack` class in Java that
extends a `Vector` (a deprecated design), a `std::stack` adaptor in C++, a
hand-built array in C, a slice in Go, and a `Vec` in Rust. Students should
notice that "stack" is a discipline, not a library, and that half of them will
never have written one.

## Problems in this pattern

| | problem | difficulty | why it is here |
|---|---|---|---|
| 1 | [valid-parentheses](valid-parentheses/) | basic | the discipline, in its smallest form |
