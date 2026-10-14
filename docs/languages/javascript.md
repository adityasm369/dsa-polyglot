# JavaScript — 1995, Brendan Eich, Netscape

## Why it was created

Netscape wanted a scripting language in the browser and wanted it to look like
Java, which was the fashion. Eich wrote the first version in **ten days**. The
name was marketing; the language has nothing to do with Java.

Almost every famous wart comes from that fortnight and from the rule that
followed it: **the web must never break**. A page from 1998 must still render,
so no mistake can ever be removed — only added around. `typeof null === "object"`
is a bug from 1995 that cannot be fixed because code depends on it.

## What it is actually good at

- **It runs everywhere, with nothing installed.** Every phone, laptop and
  television has a JavaScript engine. No other language has that reach.
- **The engines are extraordinary.** V8 and SpiderMonkey are among the most
  sophisticated JITs ever built; well-written JavaScript runs within a small
  factor of Java.
- **Asynchrony is native and ergonomic.** The event loop plus `async`/`await`
  makes I/O-heavy code read sequentially while running concurrently, with no
  threads and no locks.
- **One language across the whole stack.** Browser, server (Node), mobile
  (React Native), desktop (Electron), build tooling.
- **The largest package ecosystem in existence.** npm, for better and worse.

## What it is bad at, honestly

- **Implicit coercion.** `[] + {}`, `"5" - 3`, `0 == ""` being true. Every
  JavaScript programmer eventually memorises a table of these.
- **One number type.** Every number is a float64, so integers are exact only to
  2⁵³. `0.1 + 0.2 !== 0.3`. `BigInt` exists but does not mix with `Number`.
- **No standard library worth the name.** No built-in date handling that anyone
  trusts, no decimal type, no ordered map until recently — so the ecosystem
  filled the gap and dependency trees became enormous.
- **`this`.** Its value depends on how a function is called, not where it is
  defined. Arrow functions fixed it by not having one.
- **Single-threaded by default.** Worker threads exist; shared mutable state
  across them does not, by design.

## Where it is genuinely used

Every website with any interactivity. VS Code, Slack, Discord, Teams (Electron).
Netflix, PayPal and Uber backends on Node. React Native apps. Essentially all
front-end build tooling.

## React, specifically

React is **not a language** — it is a library for describing a user interface as
a function of state, and it is why this repository has no `react/` folder under
the problems. There is no React in which to write a binary search. What React
is good at is the thing it was built for at Facebook: keeping a complex UI
consistent with changing data without anyone hand-writing DOM updates.

For a fourth-year, the lesson worth teaching is the one idea underneath:
**the UI is a pure function of state**, and re-rendering everything is made
cheap by diffing a virtual tree. That idea is testable and transferable; JSX
syntax is not.

## Install and run

```sh
curl -fsSL https://deb.nodesource.com/setup_22.x | sudo -E bash -
sudo apt-get install -y nodejs
node --version && npm --version
```

In this repo (no dependencies — the test runner ships with Node 18+):

```sh
cd dsa/01-arrays-hashing/two-sum/javascript
node --test
```

## What a fourth-year should take from it

Open the JavaScript solution and look at why it uses `Map.has()` rather than
`if (obj[key])`. Index `0` is falsy, so the spec's `[0, 0]` case silently fails
with the second form. That one line is the whole language in miniature:
convenient, and quietly wrong unless you know the rules.
