# 02 — Two pointers

## The idea in one line

Two indices moving under a rule that never lets them cross back, so a problem
that looks like it needs every pair gets solved in one sweep.

## How to recognise it

The input is **sorted**, or it is a **string read from both ends**, or you are
about to compare every element with every other element and the comparison has
some *monotonic* structure you can exploit.

Signals:
- "is it a palindrome"
- "find a pair in a **sorted** array"
- "remove duplicates in place"
- "the most water / the largest area between two bars"
- "merge two sorted things"

## The two shapes

| shape | pointers start | move rule | example |
|---|---|---|---|
| **converging** | opposite ends | move the one that cannot be the answer | valid-palindrome, trapping-rain-water |
| **same direction** | both at 0 | one scans, one writes | remove-duplicates, sliding window (pattern 03) |

## Why it is correct, which is the hard part

For converging pointers the argument is always the same **exchange argument**:
show that the pointer you move could not have been part of any better answer,
so discarding it discards nothing. Students memorise "move the smaller one" and
cannot say why. Make them prove it. `trapping-rain-water/SPEC.md` works the
proof through, because the algorithm is three lines and the reasoning is the
entire lesson.

## What it costs

| | time | space |
|---|---|---|
| every pair | O(n²) | O(1) |
| two pointers | **O(n)** | **O(1)** |

Note the space column. Unlike hashing (pattern 01), two pointers buys the time
without paying memory — which is why it wins whenever the input is sorted.

## What the seven languages show here

`valid-palindrome` is the sharpest **string** comparison in this repository,
and strings are where the seven diverge most:

| language | what a string is | indexing a character |
|---|---|---|
| C | `char*`, ends at a zero byte | `s[i]` — a byte, not a character |
| C++ | `std::string`, knows its length | `s[i]` — still a byte |
| Java | UTF-16 `String`, immutable | `charAt(i)` — a 16-bit unit, not a code point |
| Python | sequence of code points | `s[i]` — a character, and a new string |
| JavaScript | UTF-16, immutable | `s[i]` — a 16-bit unit |
| Go | immutable bytes; `range` decodes UTF-8 | `s[i]` is a **byte**, `for i, r := range s` gives runes |
| Rust | guaranteed-UTF-8 `String`/`&str` | **`s[i]` does not compile** |

Rust refusing to index a string is not an inconvenience; it is the language
telling you that "the i-th character" is not a well-defined idea in UTF-8. Show
your students `"héllo"` in all seven and watch the byte-based ones disagree.

## Problems in this pattern

| | problem | difficulty | why it is here |
|---|---|---|---|
| 1 | [valid-palindrome](valid-palindrome/) | basic | converging pointers, and the string reckoning |
| 2 | [trapping-rain-water](trapping-rain-water/) | hard | the exchange argument, made to work for its living |
