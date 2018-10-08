---
layout: post
title: Adding make to our modular LaTeX project
series: "Modular LaTeX with make"
usereadtime: true
categories: tutorial
tags: latex, make
---

In the previous part, we used `subfiles` to create a modular LaTeX project. Now, let's use `make` to automatically
create the PDF files.

We're going to add two new dependencies:
* [`latexmk` is a tool](https://mg.readthedocs.io/latexmk.html) that can be used to more intelligently handle creating
PDF files. It automatically handles running LaTeX multiple times to update references or handle BibTeX. It essentially
acts as a wrapper that deals with the fact that LaTeX is older than Thriller.
* [GNU `make`](https://www.gnu.org/software/make/) is the main topic of discussion in this post, to handle all the
automation


