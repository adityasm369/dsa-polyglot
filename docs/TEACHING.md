# Teaching from this repository

Written for the person running the session, not the students.

## The shape of one session (90 minutes)

| | | |
|---|---|---|
| 10 min | **Read the spec together.** Not the solution — the spec. Ask what the constraints forbid. The overflow line in `two-sum/SPEC.md` is there to be noticed. | `SPEC.md` |
| 15 min | **Let them write the brute force**, in any language, and *time it* at n = 10⁴. | `python/naive.py` |
| 10 min | **Ask what question the inner loop is asking.** Lead them to "have I seen this before?" The hash table arrives on its own. | `PATTERN.md` |
| 20 min | **They write the O(n) version** and run the tests. The tests already exist, so they get told they are wrong by a machine rather than by you. | `tools/run.sh python two-sum` |
| 20 min | **Open the same problem in two other languages side by side.** This is the part no other course gives them. | `c/`, `rust/` |
| 15 min | **The language lesson.** Pick the one the problem exposes. | `docs/languages/` |

## Which language exposes what

Pick the comparison to fit the lesson, rather than showing all seven every time.

| to teach | open | and show |
|---|---|---|
| what a standard library is worth | `c/` vs `python/` | 60 lines of hash table against `dict` |
| silent wrong answers | `java/` | the test prints `int: -294967296, long: 4000000000` |
| types preventing bugs | `rust/` | `Option` and `&[i32]` — no null, no mutation, enforced |
| absent vs zero | `go/` and `javascript/` | comma-ok against the falsy-zero trap |
| abstraction without cost | `cpp/` | `std::sort` inlining the comparator |
| readability as a feature | `python/` | the solution is the algorithm and nothing else |

## Rules worth keeping

1. **Never show the solution before they have failed at it.** The tests are
   written so failing is informative.
2. **Run the sanitiser in front of them once.** `cd c && make asan` on
   deliberately broken code. Watching a memory bug get caught with a line number
   is worth an hour of lecturing about memory safety.
3. **Make them read the spec's "Common mistakes" after they finish**, not
   before. Most will recognise one of their own.
4. **Do not teach seven languages.** Teach one problem in one language, then
   use the others as evidence. The repo is a comparison, not a syllabus.

## Setting up a lab machine

```sh
sudo apt-get install -y build-essential default-jdk golang-go rustc cargo python3 nodejs
git clone <this repo> && cd dsa-polyglot
tools/run.sh                      # every language, every problem
```

If a toolchain is missing, `tools/run.sh` prints `SKIP` with the reason and
carries on — a lab machine without Rust still runs the other six.
