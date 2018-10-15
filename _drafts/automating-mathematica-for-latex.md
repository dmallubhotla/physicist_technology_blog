---
layout: post
title: Automating Mathematica
category: tutorial
tags: mathematica latex make
---

Imagine you generate a figure in a Mathematica notebook to insert into a PDF. Imagine needing to change the image and
update our PDF. You would need to re-run your Mathematica code, then re-run LaTeX. This is the sort of nightmarish
scenario that never has to happen again.

We're going to be adding a new dependency to our series
* [Mathematica](https://www.wolfram.com/mathematica/), for doing math and computing things

## Getting out of the notebook
Mathematica is a fantastic tool, but it has massive, massive structural problems that make it hard to use in a
well-designed project. Mathematica makes PHP look like Python; it makes the insanity of Javascript look as organised as
Haskell. Mathematica is not designed for good practices, which means that it hurts productivity. There are alternatives,
but unfortunately for a large number of applications, we're stuck with Mathematica.

The `*.nb` file format is an example of this bad design. Notebook files are terrible to use from a reproducibility
point of view; they depend on the kernel state, which depends on human interaction (which as we've discussed earlier,
isn't really satisfactory for physics projects). Additionally, they're terrible in source control because they include
tons of pointless display metadata. Being terrible in source control also means that notebook files are pretty poor
options for collaboration. Lastly, notebook files are terrible for reuse or distribution. Obviously, it's only a good
thing for science for people to be able to improve and expand on other people's work.

As an alternative, we're going to explore a better way to use Mathematica: creating packages.

## Mathematica packages
Mathematica packages are essentially source files for Mathematica code. They can be run as scripts, or imported to
provide code for other Mathematica packages. Packages are the standard way to distribute Mathematica code for other
people. They share most of their syntax with Mathematica notebooks, but can be run in new kernels on each evaluation,
which means that they're more repeatable.

## Back to our situation

In this series, we've been looking at a hypothetical homework set about the expression $$x^2$$. Let's say our second
homework problem is the following:

{:start="2"}
1. Draw a graph of $$x^2$$ over the range $$-10 \leq x \leq 10$$.

