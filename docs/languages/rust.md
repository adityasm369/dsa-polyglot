# Rust — 2010 at Mozilla (Graydon Hoare's side project from 2006), 1.0 in 2015

## Why it was created

Hoare began it after a lift in his building broke for the second time because
of buggy firmware. Mozilla adopted it for a concrete reason: roughly 70% of
serious security vulnerabilities in Firefox — and in Chrome, and in Windows,
by Microsoft's and Google's own published figures — were **memory safety**
bugs. Use-after-free, buffer overrun, data race. Thirty years of careful C++
had not fixed it, because the language cannot see the mistake.

Rust's claim is narrow and large: memory safety **and** no garbage collector
**and** no runtime cost. It achieves it by moving the check to compile time.
Every value has exactly one owner; borrows are tracked; the compiler refuses
to build a program where a reference could outlive what it points at.

## What it is actually good at

- **Memory safety with no runtime.** No GC pauses, no refcount traffic, C-level
  performance, and use-after-free is a compile error rather than a CVE.
- **"Fearless concurrency", which is a slogan but is also true.** A data race
  requires sharing mutable state across threads, and `Send`/`Sync` make the
  compiler reject exactly that. Rust catches at compile time the bug class that
  is hardest to reproduce at runtime.
- **The type system actually prevents bugs.** `Option<T>` means there is no
  null to forget; `Result<T, E>` means an error cannot be silently dropped; and
  `match` must be exhaustive, so adding a variant breaks every place that must
  change.
- **Cargo.** Build, test, docs, benchmarks, dependencies and publishing, one
  tool, no arguments. The best tooling of any systems language.
- **Zero-cost abstraction, genuinely.** Iterator chains compile to the same
  machine code as the hand-written loop.

## What it is bad at, honestly

- **The learning curve is real and steep.** Ownership, borrowing and lifetimes
  are a new mental model, not new syntax. Expect weeks, not days, and expect
  to fight the borrow checker and lose for a while.
- **Compile times.** Comparable to C++, which is to say slow, and the trait
  system and monomorphisation are why.
- **Async is a second language inside the language.** `Pin`, `Send` bounds and
  the choice between Tokio and async-std make it the hardest part by distance.
- **Some correct programs are rejected.** The borrow checker is conservative.
  Doubly-linked lists and graphs are awkward enough that there is a famous
  tutorial called *Learn Rust With Entirely Too Many Linked Lists* — which,
  notably, makes it a poor first language for a DSA course.
- **A small talent pool and young libraries** compared with Java or C++.

## Where it is genuinely used

The Linux kernel accepts Rust drivers as of 6.1. Windows has Rust in its
kernel. Android's Bluetooth and media stacks. Firefox's CSS engine and
renderer. Cloudflare's proxy (Pingora), Discord's state service, Dropbox's sync
engine, AWS Firecracker. npm's registry. Most new blockchain infrastructure.

## Install and run

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh   # recommended
# or: sudo apt-get install -y rustc cargo                        # older version
rustc --version && cargo --version
```

In this repo (one file per problem, so `rustc --test` — no `Cargo.toml`, no
`target/` directory to gitignore):

```sh
cd dsa/01-arrays-hashing/two-sum/rust
make test        # debug build: integer overflow PANICS, which is the point
make release     # optimised: overflow wraps instead
```

## What a fourth-year should take from it

Rust is the wrong first language for data structures and the right language for
understanding what the others let you get away with. Three things to show them
in the two-sum solution:

1. The signature is `&[i32]` — a borrow. The function *cannot* modify the
   caller's array, so invariant 3 of the spec is proven by the type rather than
   checked by a test.
2. The return is `Option<(usize, usize)>`. There is no null, and the caller
   cannot read the indices without handling the empty case.
3. Run `make test` and then `make release` and ask why overflow behaves
   differently. Debug builds panic; release builds wrap. Rust makes you choose,
   where Java and C just wrap and say nothing.
