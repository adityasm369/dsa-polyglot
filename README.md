# dsa-polyglot

**The same data-structures problem, solved the same way, in seven languages — so
the only difference on screen is the language.**

Built to teach final-year B.Tech students. Spec-driven and test-driven: every
problem has a specification written before any code, tests written from the
spec, and solutions written to pass the tests. Every test in this repository
has been run.

```
tools/run.sh                  # all seven languages, every problem
tools/run.sh rust             # one language
tools/run.sh all two-sum      # one problem, all languages
```

## Why seven and not eight

The brief named eight: Go, Rust, React, Node.js, Python, C, C++ and Java.

**React is not a language** — it is a library for building user interfaces, so
there is no React in which to write a binary search. **Node.js is not a
language** either; it is a runtime that executes JavaScript. So the solutions are
in the seven that can hold one, and React gets
[its own page](docs/languages/react.md) because the idea underneath it is worth
teaching. Shipping a folder called `react/` full of JavaScript would teach a
student something false on their first click.

| | solutions | essay |
|---|:---:|:---:|
| C · C++ · Java · Python · JavaScript · Go · Rust | yes | yes |
| React | no | yes |

## What is in here

```
specs/           why the repo is shaped this way, and what is finished
docs/languages/  one essay per language: why it exists, what it is good and
                 bad at, how to install it, where it is really used
docs/TEACHING.md how to run a 90-minute session from this material
dsa/<nn>-<pattern>/
  PATTERN.md       when to reach for this pattern and how to recognise it
  <problem>/
    SPEC.md        written first: contract, constraints, invariants,
                   complexity target, edge cases, teaching notes
    c/ cpp/ java/ python/ javascript/ go/ rust/
tools/run.sh     the test runner
```

## The rules this repo holds itself to

1. **Spec before test, test before solution.**
2. **Every test is run.** A solution that has never executed is not here.
3. **Every claim about a language is checkable** — the essays carry commands
   and real output, not adjectives.
4. **Complexity is stated and justified**, including what was rejected and why.
5. **A wrong approach is kept where it teaches** (`python/naive.py`).

## Verified against

| | version | |
|---|---|---|
| gcc | 13.3.0 | `-std=c17 -Wall -Wextra -Wpedantic -O2` |
| g++ | 13.3.0 | `-std=c++20`, sanitisers via `make asan` |
| javac / java | 21.0.12 | JDK only, no Maven or Gradle |
| python3 | 3.12.3 | standard library only |
| node | 18.19.1 | built-in test runner, no dependencies |
| go | 1.22.2 | `go vet` then `go test` |
| rustc | 1.75.0 | `rustc --test`, debug build so overflow panics |

No project in this repository has a third-party dependency. A lab machine needs
the toolchains and nothing else.

## Progress

See [specs/PROGRESS.md](specs/PROGRESS.md) — it states exactly what is finished
and what is only scaffolded, so nobody teaches from a stub by accident.

## Install everything on a lab machine

```sh
sudo apt-get install -y build-essential default-jdk golang-go rustc cargo python3 nodejs
tools/run.sh
```

A missing toolchain prints `SKIP` with the reason and the rest still runs.
