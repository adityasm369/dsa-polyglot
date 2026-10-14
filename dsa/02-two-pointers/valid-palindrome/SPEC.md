# valid-palindrome

- **Pattern:** 02 — two pointers
- **Difficulty:** basic
- **Written:** before any code in this folder

## Problem

Given a string, decide whether it reads the same forwards and backwards,
considering **only alphanumeric characters** and ignoring case.

## Contract

```
input   s: string
output  true if s is a palindrome under the rule above, else false
```

## Constraints

```
0 <= len(s) <= 2 * 10^5
s contains printable ASCII
```

**ASCII is a deliberate simplification and it is the most important line in this
spec.** The general problem over Unicode is genuinely hard: is "é" one character
or two? Does "Å" equal "Å" when one is a combining mark? Case folding in Turkish
maps 'I' to 'ı', not 'i'. Restricting to ASCII lets all seven languages agree,
and the moment it is lifted they stop agreeing — which is the lesson, and is why
`docs/languages/` has a table of what a string *is* in each.

## Invariants

1. An empty string is a palindrome. So is a string of only punctuation, because
   after filtering nothing remains and nothing is trivially symmetric.
2. The input is **not modified**.
3. No extra string is built. Filtering into a new array first is correct and
   O(n) space; the required solution is **O(1) space**, skipping as it goes.

## Complexity target

| | time | space | |
|---|---|---|---|
| filter then reverse then compare | O(n) | O(n) | the obvious answer; builds two strings |
| **required** | **O(n)** | **O(1)** | two pointers, skipping non-alphanumeric in place |

## Edge cases the tests must cover

| case | input | expected | what it breaks |
|---|---|---|---|
| empty | `""` | true | loops that assume at least one character |
| one character | `"a"` | true | pointers that cross immediately |
| only punctuation | `".,!"` | true | **the classic failure** — both pointers run off the end while skipping |
| mixed case | `"Aa"` | true | a comparison that forgot to fold case |
| digits count | `"0P"` | false | treating digits as non-alphanumeric |
| the textbook one | `"A man, a plan, a canal: Panama"` | true | — |
| nearly | `"race a car"` | false | — |
| all skipped but one | `"...a..."` | true | skip logic that steps past the last real char |

## Teaching notes

1. Ask for the one-liner first. Every student writes
   `s = filter(s); return s == s[::-1]`. It is correct. Ask what it costs: two
   new strings, O(n) extra memory. On a 200 000-character input that matters.
2. Then ask them to do it without allocating. The two-pointer version appears,
   and the bug appears with it: **`".,!"` crashes or loops** unless both skip
   loops also check `i < j`. Put that case in front of them before they run it.
3. Open the C and Rust versions together. C indexes bytes and is happy. Rust
   refuses to index at all and makes you say what you meant. Ask which one is
   being unhelpful, then show them `"héllo"`.

## Common mistakes

- Skipping without re-checking `i < j`, so `".,!"` runs off the end.
- `tolower()` in C on a `char` that is negative — undefined behaviour; the
  argument must be converted to `unsigned char` first. This is a real C trap and
  the C solution here documents it.
- Comparing before skipping, so a punctuation character gets compared.
- In Java, using `Character.toLowerCase(char)` and assuming it is the same as
  the String-level case folding. For ASCII it is; beyond ASCII it is not.
