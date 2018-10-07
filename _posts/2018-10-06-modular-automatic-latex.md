---
layout: post
title: Setting up a modular LaTeX project
series: "Modular LaTeX with make"
usereadtime: true
---
I've had a few occasions to use project structures that involved multiple independent sections of a
LaTeX document, with individual `.pdf` files for each section, while retaining the ability to create a complete `.pdf`
for the entire project. This series will be about making that possible, while adding automation to handle external data
and results in a way that's easy to use.

Some examples of projects I've found this helpful include
* homework: I may want to edit / share problems separately
* lecture notes: I might want the ability to create files for each day, but keep a full `.pdf` of the whole lecture
series
* research notebooks: it's helpful as a way to organise thoughts on different topics in a very easy to read way, if
`.pdf` files are preferable to something like a wiki.

Modularity with different files brings several advantages. It lets you isolate things that are operated independently,
and makes it simple to merge or split projects as sections grow larger. It also lets you keep dependencies organised
logically, instead of doing something more ad-hoc.