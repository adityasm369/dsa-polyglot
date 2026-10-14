# C++ — 1985, Bjarne Stroustrup, Bell Labs

## Why it was created

Stroustrup had used Simula, which had classes and made large programs easy to
structure, and found it too slow for real work. He had used BCPL, which was
fast and made large programs painful. C++ began as "C with Classes": keep C's
cost model and add the structure Simula had, with the rule that **you do not
pay for what you do not use**.

That rule explains the whole language. Virtual functions cost a pointer
indirection — so they are opt-in. Exceptions cost space — so there is a flag
to remove them. Templates cost compile time and nothing at runtime, which is
why the standard library is templates.

## What it is actually good at

- **Abstraction with no runtime bill.** `std::sort` on a vector of ints
  compiles to tighter code than C's `qsort`, because the comparison is inlined
  rather than called through a function pointer. This is rare and real.
- **RAII.** A resource is owned by an object, and the destructor runs when
  scope ends — including when an exception unwinds. Once you have internalised
  it, manual `free`/`close`/`unlock` look like bugs waiting to happen.
- **The standard library is a DSA textbook.** `vector`, `map`, `unordered_map`,
  `set`, `priority_queue`, `deque` with documented complexity guarantees, plus
  `<algorithm>`. For competitive programming this is decisive.
- **You can descend.** When you need a raw pointer, inline assembly or a
  specific instruction, C++ lets you, in the same file as the abstraction.

## What it is bad at, honestly

- **It is enormous.** The standard is over 1,800 pages. Nobody knows all of
  C++. Every team uses a different subset, and reading another team's C++ means
  learning their subset first.
- **It inherited every C footgun and added its own.** Dangling references,
  iterator invalidation, object slicing, the rule of three becoming the rule of
  five becoming the rule of zero, and five kinds of initialisation syntax that
  do not agree.
- **Compile times.** Templates are evaluated at compile time, so heavy template
  code can take minutes, and the errors can run to hundreds of lines for a
  single missing `const`.
- **No standard build or package tooling.** CMake, Make, Bazel, Conan, vcpkg —
  everyone picks. Compare `cargo build`.

## Where it is genuinely used

Unreal and Unity engines. Chrome, Firefox and Safari's rendering engines.
MySQL and MongoDB. Adobe Photoshop. Most high-frequency trading. LLVM. CERN's
physics analysis. Bloomberg terminals. Anywhere performance and large-scale
structure are both required.

## Install and run

```sh
sudo apt-get install -y build-essential     # Debian / Ubuntu
g++ --version
```

In this repo:

```sh
cd dsa/01-arrays-hashing/two-sum/cpp
make test
```

Compiled `-std=c++20 -Wall -Wextra -O2`. Sanitisers are one flag away and
worth your students' time: `make asan` builds with
`-fsanitize=address,undefined`, which turns a silent memory bug into a precise
error with a line number.

## What a fourth-year should take from it

This is the language their placement interviews will most likely be solved in,
and the one where "it works" and "it is correct" diverge most. Teach
`-fsanitize=address` early. A student who has watched the sanitiser catch an
off-by-one in their own binary search learns more in ten seconds than in an
hour of slides.
