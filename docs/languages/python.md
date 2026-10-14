# Python — 1991, Guido van Rossum, CWI Amsterdam

## Why it was created

Van Rossum had worked on ABC, a teaching language that was pleasant and
unusable for real work because it could not call the operating system. Over a
Christmas holiday he started a successor that kept ABC's readability and added
the one thing it lacked: the ability to be extended in C. That is the whole
design. Python is a readable language wrapped around a C extension mechanism,
which is why the scientific stack exists — NumPy is not fast Python, it is C
with a Python interface.

The guiding idea is that **code is read far more often than it is written**,
so the language optimises for the reader.

## What it is actually good at

- **The shortest distance from idea to working program.** Fewer lines, no build
  step, no types to declare. For teaching an algorithm, this matters: the
  solution file contains the algorithm and nothing else.
- **It is the glue of scientific and AI computing.** NumPy, pandas, PyTorch,
  scikit-learn. The heavy work is C, CUDA and Fortran; Python orchestrates it.
  Virtually all AI research is published as Python.
- **A standard library that is genuinely batteries-included.** The whole Job
  Hunter and Pro Agentic projects in this estate are standard-library-only,
  including an HTTP server, a SQLite client and a Kafka protocol implementation.
- **Readable by non-programmers.** Hand Python to a domain expert and they can
  usually follow it.

## What it is bad at, honestly

- **Speed. By a factor of 10 to 100 on pure-Python loops.** Every integer is a
  heap object; every loop iteration is bytecode dispatch. The two-sum naive test
  in this repo takes about a second in Python and 40 ms in C++.
- **The GIL.** Until recently, one Python thread executed bytecode at a time, so
  threads gave concurrency but not CPU parallelism. 3.13 ships an experimental
  free-threaded build; it is not yet the default and is not yet fast.
- **Dynamic typing finds your bugs in production.** Type hints and mypy help a
  great deal, but they are optional and unenforced at runtime.
- **Packaging has been a decade-long embarrassment.** pip, venv, conda, poetry,
  pipenv, uv. Compare `cargo` or `go mod`.
- **Memory.** A Python list of a million ints uses roughly 10× what a C array
  does.

## Where it is genuinely used

Instagram (one of the largest Django deployments anywhere). Dropbox's client.
YouTube. Reddit. Essentially all machine learning research and most production
inference orchestration. Scientific computing from CERN to genomics. DevOps
tooling: Ansible, and most of the internal glue at every company.

## Install and run

```sh
sudo apt-get install -y python3 python3-pip    # usually already present
python3 --version
```

In this repo (no dependencies, the test runner is in the standard library):

```sh
cd dsa/01-arrays-hashing/two-sum/python
python3 -m unittest -v
```

## What a fourth-year should take from it

Use Python to teach the *idea* and another language to teach the *cost*. Write
the solution here first — it will be the clearest of the seven — then open the
C version and count the lines. The difference is what Python is doing for you,
and the runtime is what you pay for it.
