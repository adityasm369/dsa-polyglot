# valid-parentheses

- **Pattern:** 04 — stack
- **Difficulty:** basic
- **Written:** before any code in this folder

## Problem

Given a string containing only the characters `()[]{}`, decide whether it is
valid: every opening bracket is closed by a bracket of the same type, in the
correct order, and every closing bracket has a matching opener.

## Contract

```
input   s: string over the six bracket characters
output  true if the brackets are balanced and correctly nested, else false
```

## Constraints

```
1 <= len(s) <= 10^4
s consists only of '()[]{}'
```

## Invariants

1. **Nesting, not counting.** `([)]` has equal numbers of each bracket and is
   still invalid. A counter cannot solve this problem; that is the point.
2. The input is **not modified**.
3. Extra space is O(n) in the worst case (every character is an opener), and
   the function reads each character exactly once.

## Complexity target

| | time | space | |
|---|---|---|---|
| repeatedly delete `()`, `[]`, `{}` until nothing changes | O(n²) | O(n) | correct, quadratic |
| count each bracket type | O(n) | O(1) | **wrong** — accepts `([)]` |
| **required: stack of openers** | **O(n)** | **O(n)** | |

## The discipline

Walk left to right.

- An opener goes on the stack.
- A closer must match the **top** of the stack, and is then popped.
- A closer with an empty stack, or a mismatch, is invalid immediately.
- At the end the stack must be empty.

The two conditions that people forget are both at the end: an empty stack at the
close proves the closer had something to match, and an empty stack at the end
proves nothing was left open. `(` alone passes every other check and fails only
the last one.

## Edge cases the tests must cover

| case | input | expected | what it breaks |
|---|---|---|---|
| single opener | `(` | false | accepting because nothing mismatched |
| single closer | `)` | false | popping an empty stack |
| simple | `()` | true | — |
| all three types | `()[]{}` | true | a lookup that handles only one type |
| nested | `([{}])` | true | — |
| interleaved | `([)]` | false | **the counting trap** |
| prefix closes too early | `)(` | false | checking the stack only at the end |
| left open | `(((` | false | forgetting the final empty check |
| long balanced | 5000 nested pairs | true | recursion, if used, overflows |

## Teaching notes

1. Ask students to write a counter first. It passes the spec's common cases and
   fails `([)]`. Have them find that case themselves. Then ask what information
   a counter throws away.
2. Ask what "the most recent unclosed opener" means in ordinary English, then
   show them that the stack is exactly that sentence.
3. Ask why the same algorithm solves HTML tag matching and the call stack. It is
   the same discipline.

## Common mistakes

- Using a counter instead of a stack.
- Checking the top of an empty stack. In C, C++ and Rust this reads garbage or
  panics; in Python and JavaScript `stack[-1]` and `stack.at(-1)` need care.
- Forgetting the final `stack is empty` check.
- Mapping closers to openers backwards, so `)` is compared with `(` only by
  accident.
