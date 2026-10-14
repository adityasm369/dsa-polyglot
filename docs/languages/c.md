# C — 1972, Dennis Ritchie, Bell Labs

## Why it was created

Unix was written in assembly and could not be moved to a new machine without
rewriting it. Ritchie needed a language close enough to the hardware to write
an operating system, and portable enough that the operating system could be
recompiled elsewhere. C is the smallest language that makes that possible: it
is a thin, typed layer over what a CPU actually does.

Everything people find hostile about C — manual memory, no bounds checks, no
strings — follows from that goal. A bounds check C did not ask for is a cost
the kernel cannot pay.

## What it is actually good at

- **Predictable cost.** Every line maps to a handful of instructions. There is
  no garbage collector pausing, no hidden allocation, no vtable lookup you did
  not write. When you need to know what the machine will do, C tells you.
- **Portability by recompilation.** A C compiler exists for essentially every
  processor ever shipped, including microcontrollers with 2 KB of RAM.
- **It is the interface between everything.** Python, Java, Go, Rust, Node —
  all of them call C libraries, and all expose a C ABI. C is the lingua franca
  of linking.
- **Small enough to hold in your head.** The entire language is about 40
  keywords. You can read the standard.

## What it is bad at, honestly

- **Memory is yours, including the mistakes.** Use-after-free, double-free,
  buffer overrun and leak are all ordinary C bugs, and the compiler will not
  mention them. Decades of remote code execution vulnerabilities come from
  exactly this.
- **No strings, no collections.** A string is a pointer and a convention: the
  bytes end at the first zero. There is no list, no map, no set. You write
  them, or you link something.
- **Undefined behaviour is a trap door.** Signed overflow, reading
  uninitialised memory, aliasing violations — the standard says the compiler may
  do anything, and modern optimisers do. A program that works at `-O0` and
  breaks at `-O2` is usually your fault, not the compiler's.
- **No namespaces, no modules, no generics.** Large C programs stay readable by
  discipline alone.

## Where it is genuinely used

Linux, Windows and macOS kernels. SQLite, which is on every phone. Redis.
PostgreSQL. OpenSSL. FFmpeg. CPython itself. Every microcontroller in a car,
a pacemaker, a washing machine. If software must run where there is no
operating system, it is C.

## Install and run

```sh
sudo apt-get install -y build-essential     # Debian / Ubuntu
gcc --version
```

In this repo:

```sh
cd dsa/01-arrays-hashing/two-sum/c
make test          # compiles and runs the assertions
make clean
```

Compiled with warnings treated as information you want:
`-std=c17 -Wall -Wextra -O2`. Memory checking, if valgrind is present:
`make memcheck`.

## What a fourth-year should take from it

Write one data structure in C before you trust any other language's version.
Implementing a hash map — choosing the bucket count, handling collision,
deciding when to grow, freeing it correctly — teaches more about
`dict`/`HashMap`/`map` than any amount of using them. The DSA solutions here
in C are deliberately the longest, and that length is the lesson.
