---
layout: post
title: Software I use
date: 2018-10-04 15:00:00 -0500
usereadtime: true
---
Here's a list of some of the software tools I use most frequently for physics
projects.

I don't intend on writing tutorials for each of these  tools individually. Most of these tools are very popular, and
have spectacular tutorials already written for them. One thing I intend to do is to try to write about how to make them
work together more smoothly with less effort.

Here's the list:
* [Git](https://git-scm.com/), for version control
* [LaTeX](https://www.latex-project.org/), or another `TeX` variant, for typesetting
* [Mathematica](https://www.wolfram.com/mathematica/), for math
* [Python](https://www.python.org/), for general computing and with [`scipy`](https://www.scipy.org/) for computations
* [Make](https://www.gnu.org/software/make/), for automating builds and making life more magical

## Git
[Git](https://git-scm.com/), or less ideally another version control system, is the single most useful tool I've ever
used, in any context. I assumed it was widely used, but asking around, it seems like it isn't. I often say that things
that happen outside version control don't count. Spending a half hour learning how to use Git will save you tons of
time in the future.

Version control essentially keeps track of different versions of files as you edit them. This lets you revert changes
to a file if you ever make a mistake, it lets you use multiple versions of a directory (so you can try testing out some
changes to some files, while leaving the original versions available if you ever need to switch back and forth). VCSs
also let you intelligently merge changes, whether because you and a collaborator are working on the same file or because
you happen to have two sets of changes you want to work on at the same time.

If you want to make collaboration a breeze, you can either connect to something like [GitHub](https://github.com/)
or [Bitbucket](https://bitbucket.org/), hosting services which let you upload your code, along with all of its version
history. You can make repositories private or pubic, or even set up your ownserver if you want to collaborate but don't
want your code to leave your control. Hosting services like that are separate from using Git, and aren't required to get
the version management, but are another great part of your workflow. [Here's this blog in GitHub!]({{site.github.repo}})

This is separate from tools like Dropbox or its competitors. Those types of services are mostly intended as ways to
backup a file system. If you want to create copies of your entire `Documents` folder, put it on Dropbox. Git is much
more about keeping track of the history of a single project, and simplifying your workflow.

The pros:
* Git allows you to handle file history intelligently, no matter what you're doing on your computer. If your computer
use involves modifying files, Git will let you track it, share it with other computers and live a more fulfilled life.
* Git is an incredibly popular tool, which means that it's been optimised on every platform, and has a huge ecosystem
built around it. Don't like the command line? There are a thousand tools that let you use Git with a GUI. Have too many
options? Try using more restrictive workflows.

The cons:
* What cons?

## TeX
[The obnoxiously capitalised LaTeX](https://www.latex-project.org/) is ubiquitous in physics, as the de facto
standard way to generate documents. The best parts of TeX come from its age: TeX has had 40 years of extensions,
forks and packages built for it. I use `pdfTeX` for actual document generation, but with `latexmk` as a tool to handle
the actual builds. TeX is a tool of necessity; as a de facto standard, its flaws are deeply embedded. There are powerful
variants like `LuaTeX`, but vendor lock-in can be a dangerous thing. It's not necessarily clear what the future holds
for `LaTeX`. The massive rewrite in progress sounds promising, but
[massive rewrites cause problems](https://www.joelonsoftware.com/2000/04/06/things-you-should-never-do-part-i/).

My strategy for dealing with highly fragmented ecosystems is to try to stay as vanilla as possible for the central
features, so that if variants suddenly go away, your own projects don't end up broken. Each additional dependency in a
project introduces a new point of failure; for widely-used dependencies like `LuaTex`, the risk might be low, but for
others it might be higher. The best way to mitigate that risk is to decouple it: I use `latexmk` for builds, but
only in ways that

The pros:
* How else are you going to typeset math?

The cons:
* Want to include external data natively? Have fun without Lua. Edit an equation name? Don't forget to build twice!
TeX is old and brittle, and it constantly forces you to operate in the wrong abstraction layer (which is one of my least
favourite things to be forced to do). Using a TeX variant for type setting involves abstractions so leaky that you could
make a flavourful spring soup with them.

## Mathematica
[Mathematica](https://www.wolfram.com/mathematica/) is one of my main tools for handling math. They share a feature set,
but I find that one big difference between Mathematica and a tool like Matlab is that Matlab is much more about
_computation_, as opposed to _math_. For anyone who has ever wanted to skip the boring parts of a homework problem,
Mathematica needs no introduction.

However, Mathematica is also one of the most fickle software platforms I've ever used. Mathematica uses a language
designed for people who don't use languages, and that can lead to weird syntax that can make PHP looks sane. There are
even weirder design decisions, like weird variable handling in the kernel that almost seems designed to create bugs, frequent issues
with accuracy of built-in functions, the hard-to-justify emphasis on `.nb` files, which ties backend execution to the
frontend and an almost deliberate discouraging of good programing practices by typical users.

There are ways to make Mathematica work for you, but they're often not the first thing that Mathematica suggests. We'll
find occasions to talk about Mathematica more.

The pros:
* Mathematica is the best symbolic algebra platform out there
* Mathematica has built-ins for nearly everything you could ever want...

The cons:
* ...except for that one particular thing you need right now
* There are several different ways to create format strings in Mathematica. Here's one:
```wl
ToString@StringForm["The value of Pi is ``", NumberForm[N[Pi], 3]]
```
If you don't like that, try creating something with `TemplateApply`. Then reconsider your life choices, and switch to
something like Python.

## Python
[Python](https://www.python.org/) is a good programming language for general programming. Writing programs, or even
just writing simple scripts, is only going to get more useful for physicists, and using really popular languages grants
access to vibrant ecosystems. Python in particular is easy to read, and is good for both scripts and whole applications.

For physics specifically, I've found `scipy` and `numpy` to be excellent substitutes for Matlab, with the full strength
of Python available for other tasks like file I/O or creating interfaces.

The pros:
* The full strength of a full-featured, real life programming language not designed by scientists

The cons:
* The only real con is just taking the time to learn it. Python is very readable, though, so unlike legacy languages
like COBOL it's not a huge pain to learn.

## Make
[Make](https://www.gnu.org/software/make/) is a build automation tool. It's a really old utility that lets you specify
two things: which files depend on which other files, and how to create/update a file whenever it's missing / out of date.

The great benefit of `make`, like all the great *nix utilities, is that it's unbelievably flexible. It only does one
thing, automating builds, but it does it ridiculously well. I mentioned
[in a previous post]({% post_url 2018-10-04-introducing-this-blog %}) that having a one-step build was important.
`make` is the tool that accomplishes that.

It isn't a tool available on Windows by default, but I use Cygwin as a CLI, which gives me access to `make`. There are
other great build automation tools out there; for projects primarily in a particular language like Python, Javascript
or Java, there are specific build tools that are commonly used for those languages. I've found that `make` handles a
large number of my typical use cases, so I use it fairly consistently. There are situations when being able
to use the full power of something like Gradle is helpful, or so I assume, but none that I've ever run across in
physics. If you're connecting multiple different languages together, like trying to use Mathematica to generate
figures which then get included in a document by LaTeX, `make` really shines.

The pros:
* Once you have it set up properly, your life becomes much easier

The cons:
* Setting it up on projects can be a chore; we'll talk about how to do it though