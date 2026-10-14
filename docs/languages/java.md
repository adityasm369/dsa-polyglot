# Java — 1995, James Gosling, Sun Microsystems

## Why it was created

Sun's team was building software for consumer devices — set-top boxes, in
practice — and found C++ impossible to ship across chips that changed every
product cycle. They wanted a language that compiled **once** and ran anywhere a
small virtual machine could be ported. The web arrived mid-project, applets
gave Java its first audience, and the applets died. What survived was the
promise underneath: *write once, run anywhere*, meaning the JVM is the thing
that gets ported, not your program.

The deliberate omissions are the design: no manual memory management, no
pointer arithmetic, no multiple inheritance, no operator overloading. Gosling's
stated aim was that an average team should not be able to shoot itself in the
foot.

## What it is actually good at

- **The JVM is the best general-purpose runtime in existence.** Decades of work
  on generational garbage collection and just-in-time compilation mean
  long-running Java gets *faster* as it runs: the JIT watches which branches are
  taken and recompiles hot code with that knowledge. A warmed JVM can beat
  naively-written C++.
- **Backwards compatibility that is almost absurd.** Code compiled in 1998 very
  often still runs. For a bank with a 25-year-old core system, this is not a
  nice-to-have, it is the entire reason.
- **Tooling and libraries nothing else matches.** IntelliJ's refactoring,
  Maven and Gradle, JUnit, and a library for genuinely everything.
- **Concurrency built in and well understood.** The Java Memory Model was the
  first mainstream, formally specified answer to "what can one thread see of
  another", and `java.util.concurrent` is still a reference implementation.

## What it is bad at, honestly

- **Verbosity, though far less than its reputation.** Records, `var`, switch
  expressions and text blocks have fixed much of it. The reputation is from
  Java 6 and people repeat it without checking.
- **Boxing.** `List<Integer>` stores pointers to heap objects, not ints. A list
  of a million numbers is a million allocations and a cache-miss per access.
  This is the single biggest reason Java loses numeric benchmarks, and why
  Project Valhalla exists.
- **Startup time.** The JVM must start and the JIT must warm up, which makes
  plain Java a poor fit for short-lived serverless functions. GraalVM native
  images address it at the cost of reflection.
- **Memory footprint.** A JVM's baseline is tens of megabytes before your code.
- **Checked exceptions.** A well-meant idea that in practice produced millions
  of empty `catch` blocks.

## Where it is genuinely used

Essentially every large bank's core systems. Android (the SDK and most apps).
Hadoop, Spark, Kafka, Elasticsearch, Cassandra — the data infrastructure the
industry runs on. Netflix, LinkedIn, Uber backends. Minecraft.

## Install and run

```sh
sudo apt-get install -y default-jdk    # Debian / Ubuntu
javac -version && java -version
```

In this repo (no Maven or Gradle needed — a JDK is enough):

```sh
cd dsa/01-arrays-hashing/two-sum/java
javac -Xlint:all Solution.java SolutionTest.java
java SolutionTest
```

## What a fourth-year should take from it

This is most likely the language their interviews will be in, so teach them the
costs they cannot see. Run the two-sum test and read the line it prints:
`int: -294967296, long: 4000000000`. Java will not warn you that your sum
overflowed — it wraps silently and returns a wrong answer. Then ask why
`HashMap<Long, Integer>` allocates and `long[]` does not.
