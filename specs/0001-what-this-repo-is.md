# 0001 — What this repository is, and what it refuses to be

- **Status:** accepted
- **Date:** 2026-10-14
- **Audience:** final-year B.Tech students, taught by him

## Evidence

His brief: a single repo for learning concepts across Go, Rust, React, Node.js,
Python, C, C++ and Java; basic / medium / hard solutions to the most common DSA
problems; spec-driven and test-driven; special weight on each language's pros
and cons, why it was created, how to install and run it, and where it is really
used; "structured like a real pro, organized for advanced learners."

Asked whether the solutions should span three languages or all of them, he said
**all**.

## One correction, made in the open

**React cannot hold a DSA solution.** It is a view library for building user
interfaces, not a language and not a runtime — there is no React in which to
write a binary search. Node.js is also not a language; it is a runtime that
executes JavaScript. So:

| | solutions | written material |
|---|---|---|
| C, C++, Java, Python, Go, Rust | yes | yes |
| JavaScript (run on Node.js) | yes | yes |
| React | **no** | yes |

That is **seven implementations per problem**, not eight. Pretending otherwise
would mean shipping a folder named `react/` containing JavaScript, which
teaches a fourth-year student something false on their first click.

## What the repository is for

A student who has finished a DSA course can usually solve a problem in one
language and has no idea what the language itself is costing them. This repo is
built around the comparison: the *same* problem, solved the *same* way, in seven
languages, so the difference on screen is the language and nothing else.

That is why the solutions are deliberately **not** idiomatic-per-language where
idiom would change the algorithm. A Python one-liner using `collections.Counter`
and a hand-rolled Java `HashMap` loop do not teach a comparison; they teach that
Python has a standard library. Where idiom and comparability conflict, the repo
shows **both** and says which is which.

## Rules the repo holds itself to

1. **Spec before test, test before solution.** Every problem has a `SPEC.md`
   written before any code: the statement, the constraints, the invariants, the
   complexity target, and the edge cases that must be handled. The tests are
   written from the spec. The solutions are written to pass the tests.
2. **Every test is run.** A solution that has never been executed is not in the
   repository. CI runs all seven languages on every push, and the README states
   which toolchain versions it was verified against.
3. **Every claim about a language is checkable.** "Rust is safe" is not a claim,
   it is a slogan. "Rust rejects this program at compile time, and here is the
   error" is a claim — so the language essays carry commands and real output.
4. **Complexity is stated and justified.** Every solution declares its time and
   space complexity in a comment, and the spec says what the target was and why.
5. **A wrong approach is shown where it teaches.** The naive version is kept
   alongside the good one when the gap between them is the lesson.

## Structure

```
docs/languages/<lang>.md     why it exists, pros, cons, install, real use
docs/TEACHING.md             how to run a session from this repo
dsa/<nn>-<pattern>/
  PATTERN.md                 when to reach for it, and how to recognise it
  <problem>/
    SPEC.md                  written first
    c/ cpp/ java/ python/ javascript/ go/ rust/
tools/run.sh                 run one language, or all of them
.github/workflows/ci.yml     all seven, on every push
```

## Out of scope

A problem-count race. Fifty half-finished problems teach nothing; the repo
grows one complete pattern at a time, and `specs/PROGRESS.md` states exactly
what is finished and what is not, so nobody teaches from a stub by accident.
