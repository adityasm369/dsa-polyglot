# Go — 2009, Robert Griesemer, Rob Pike and Ken Thompson, Google

## Why it was created

The three of them were waiting for a C++ binary to compile. Google's codebase
had reached a size where builds took the better part of an hour, dependency
graphs were unanalysable, and onboarding an engineer onto a C++ service took
months. Pike has said the aim was not a better language for *him* — it was a
language in which a new graduate could be productive in a week and could not
easily write something unmaintainable.

So Go is defined by what it refuses. No inheritance. No exceptions. No
generics for its first thirteen years. No operator overloading. One formatter
with no options, so nobody argues about braces. The language is small enough
that its specification is about 90 pages, and deliberately boring.

## What it is actually good at

- **Concurrency as a first-class idea.** A goroutine costs about 2 KB and the
  runtime multiplexes hundreds of thousands onto a few OS threads. Channels make
  communication the default and shared memory the exception. For network
  services this is the best model in mainstream use.
- **Compile speed.** Seconds, not minutes, because the import graph is a DAG
  with no circular imports allowed and no textual header inclusion.
- **One static binary.** `go build` produces a single file with no runtime to
  install. Deployment is `scp`. This alone explains Go's dominance in
  infrastructure.
- **A standard library that is production-grade.** A real HTTP/2 server, TLS,
  JSON, and a testing framework with benchmarking, all in the box.
- **`gofmt`.** The argument about formatting is simply over.

## What it is bad at, honestly

- **`if err != nil` everywhere.** Explicit error handling is honest and it is
  also a third of the lines in some files. Readable, and tiring.
- **Generics arrived in 1.18 and are limited.** Thirteen years of
  `interface{}` and code generation left scars in older libraries.
- **The garbage collector is tuned for latency, not throughput.** Pauses are
  sub-millisecond, which is excellent; raw allocation-heavy throughput trails
  Java and C++.
- **`nil` is several different things.** A nil map reads fine and panics on
  write; a nil interface holding a nil pointer is not equal to nil. This is the
  classic Go trap.
- **Deliberately unexpressive.** No sum types, no pattern matching, no
  `Option`. Some problems want those, and Go's answer is that you do not need
  them.

## Where it is genuinely used

Docker. Kubernetes. Terraform. Prometheus. Etcd. CockroachDB. Most of the
cloud-native stack is Go, and that is not a coincidence — a single static
binary with great concurrency is exactly what infrastructure wants. Also
Cloudflare's edge, Uber's and Twitch's services, and Dropbox's migration from
Python.

## Install and run

```sh
sudo apt-get install -y golang-go        # Debian / Ubuntu
# or, for the current release:
# wget https://go.dev/dl/go1.23.linux-amd64.tar.gz
# sudo tar -C /usr/local -xzf go1.23.linux-amd64.tar.gz   # add /usr/local/go/bin to PATH
go version
```

In this repo:

```sh
cd dsa/01-arrays-hashing/two-sum/go
go vet ./...        # catches real mistakes, run it before the tests
go test ./...
go test -bench=.    # the benchmark harness is built in
```

## What a fourth-year should take from it

Two things. First, read the comma-ok lookup: `i, ok := seen[want]` separates
"absent" from "present and zero" in one line — the exact distinction the
JavaScript version gets wrong with `if (map[k])`. Second, run
`go test -bench=.` and notice that benchmarking required no library, no
decorator and no setup. Go's view is that if a thing matters, it belongs in the
toolchain.
