# React — 2013, Jordan Walke, Facebook

> **React is not a language, and that is why this repository has no `react/`
> folder under the problems.** It is a JavaScript library for building user
> interfaces. There is no React in which to write a binary search. This page
> exists because it was on the brief and because the idea underneath it is
> worth a lecture; the solutions live under `javascript/`.

## Why it was created

Facebook's chat was persistently, visibly wrong: an unread badge showing a
count that did not match the inbox. The cause was the standard architecture of
the day — many pieces of code mutating the DOM directly, each correct on its
own, collectively unable to agree on the truth. Walke's answer was to stop
describing *changes* and start describing *the result*: given this state, the
screen looks like this. Re-render everything, and make that affordable by
diffing a lightweight copy of the tree in memory before touching the real DOM.

## The idea worth teaching

**UI = f(state).** The interface is a pure function of data. You never write
"add a row to the table"; you change the data and the table follows. That is a
genuinely transferable idea — SwiftUI, Jetpack Compose and Flutter are all the
same insight — and it is independent of JSX, hooks or any React API.

The second idea is **reconciliation**: comparing two trees to find the minimum
set of real changes. That is a diffing algorithm, and so it is the one part of
React that belongs near a DSA course. Ask your students how they would diff two
trees, then show them that React does not solve it in general — it assumes that
elements at the same position are the same element, and asks you for a `key`
when they are not. An O(n³) problem turned into O(n) by a well-chosen
assumption is a better lesson in algorithm design than most textbook chapters.

## What it is actually good at

- **Complex UI stays consistent** without anyone hand-coordinating updates.
- **Components compose.** A component is a function returning a description;
  functions compose, so interfaces do.
- **One mental model across web, native and desktop** via React Native and
  Electron.
- **The largest front-end ecosystem**, so almost nothing needs building.

## What it is bad at, honestly

- **It is not simple, only familiar.** Hooks have real rules — call order
  matters, dependency arrays are hand-maintained, stale closures are a routine
  bug — and none of it is obvious.
- **Re-rendering is cheap, not free.** Large applications spend real engineering
  effort on `memo`, `useMemo` and `useCallback` to undo work React created.
- **You must pick everything else.** Routing, state, data fetching, forms,
  build. React has an opinion about rendering and nothing else, which is why two
  React codebases can look nothing alike.
- **The ecosystem churns.** Class components, then hooks, then server
  components. Tutorials rot quickly.
- **Bundle size.** It ships to the user over the network, every time.

## Where it is genuinely used

Facebook and Instagram. Netflix's and Airbnb's interfaces. WhatsApp Web.
Discord. The dashboards of most SaaS products built since about 2016. React
Native: Instagram, Shopify, Discord's mobile apps.

## Install and run

```sh
node --version          # React needs Node to build, not to run
npm create vite@latest my-app -- --template react
cd my-app && npm install && npm run dev
```

## A teaching suggestion, if you want React in the course

Have them build an **algorithm visualiser** — render the array as bars, make
each step of a sort or a binary search a state change, and let React redraw.
It teaches the `UI = f(state)` idea honestly, it makes the algorithms in this
repo visible, and it gives the fourth-years something to put in a portfolio.
It is not in this repository because it is a different kind of artefact from a
tested solution, and mixing them would blur what the repo is for.
