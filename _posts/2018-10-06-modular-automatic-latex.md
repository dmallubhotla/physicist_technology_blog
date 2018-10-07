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
* large written works: for something like a book with multiple chapters, it can be unwieldy editing and or viewing the
entire work. Modularity lets you share a specific chapter with someone without hassle.

## Where do we start?

We start at Modularity.
Modularity with different files brings several advantages. It lets you isolate things that are operated independently,
and makes it simple to merge or split projects as sections grow larger. It also lets you keep dependencies organised
logically and locally, instead of doing something more ad-hoc. We'll see some examples of that.

The code for this series will be available at [this GitHub repository](https://github.com/dmallubhotla/modular_latex/).
For this post specifically, the source can be downloaded
[from this tag](https://github.com/dmallubhotla/modular_latex/releases/tag/part1), or be browsed directly in GitHub
[at this commit](https://github.com/dmallubhotla/modular_latex/tree/4445ffb73cea4b99b75470f2ba2ce3e48fe67584).

### Dependencies you'll need to get started:
* Some sort of TeX distribution. I've used MiKTeX on Windows
* The [`subfiles` package from CTAN](https://ctan.org/pkg/subfiles?lang=en), which you can install however you install
other TeX packages.

## The situation

You get a homework assignment about the newly discovered expression $$x^2$$. You start by reading the first problem:
1. What's an adjective that can be used to describe this expression?

The simplest place to start would be to create a single `.tex` file that looks something like this:
```tex
% main.tex
\documentclass{article}

\title{Homework}

\begin{document}

\maketitle

\section{Problem 1}
Quadratic.

\end{document}
```

However, for the sake of modularity, we might want to put problem 1 into its own `.tex` file. My preferred way to do this
is to use the [`subfiles` CTAN package](https://ctan.org/pkg/subfiles?lang=en). There's a ton of great material out
there about how to use it, so I won't try to write a full tutorial on it. We'll just include a very simple example.

We have a huge amount of flexibility in terms of how we can structure our folder; my personal preference is to do
something like this (including only the relevant source files):
```
.
├── problems
|   └── Problem1
|        └──Problem1.tex
└── main.tex
```
Within the `problems` folder, I like to create a separate folder for each individual problem. This is redundant and
unnecessary when the only thing in each problem folder is a `.tex` file, but we'll see how it can be helpful when a
particular problem involves several different types of source files to deal with. I also like to keep the specific
problem folder name the same as the actual `.tex` file name. There's no particular benefit from that in particular,
but having a consistent filename scheme makes automation a little bit easier, as we'll see once we start automating our
build.

To use `subfiles`, our files will need to look something like this:
```tex
% Problem1.tex
\documentclass[../../main.tex]{subfiles}

\begin{document}

\section{Problem 1}
Quadratic.

\end{document}
```

```tex
% main.tex
\documentclass{article}

\usepackage{subfiles}

\title{Homework}

\begin{document}

\maketitle

\subfile{problems/Problem1/Problem1}

\end{document}
```

Notice how we didn't need to repeat the `\usepackage{subfiles}` or the fact that the document class was `article`. When
using `subfiles`, the individual subfiles inherit the preamble of their parent file. The annoying part of the package
is needing to specify the actual `.tex` file location in both the parent file and in the subfile. (In the subfile, the
`..` means to go up a directory, for those not already familiar with that). When calling `\subfile{}`, the `.tex` file
extension is assumed, so that doesn't need to be specified separately, but it does from within the subfile.

Now that we have both of these files, we can do some cool things. You can generate a document using `main.tex` like normal,
and `main.pdf` will look the exact same as it did earlier. However, you can also generate a document directly from
`Problem1.tex`, which will only include the text within that document. That's what allows us to share separate `.pdf`
files for each problem. Next time, we'll take a look at how to automate that.