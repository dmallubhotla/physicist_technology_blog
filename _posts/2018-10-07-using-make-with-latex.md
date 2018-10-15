---
layout: post
title: Adding make to our modular LaTeX project
series: "Modular LaTeX with make"
categories: tutorial
tags: latex make
---

In the previous part, we used `subfiles` to create a modular LaTeX project. Now, let's use `make` to automatically
create the PDF files.

We're going to add two new dependencies:
* [`latexmk` is a tool](https://mg.readthedocs.io/latexmk.html) that can be used to more intelligently handle creating
PDF files. It automatically handles running LaTeX multiple times to update references or handle BibTeX. It essentially
acts as a wrapper that deals with the fact that LaTeX is older than Thriller. Incidentally, many TeX IDEs are able
to use `latexmk` as their default build tool, which is something I recommend setting up.
* [GNU `make`](https://www.gnu.org/software/make/) is the main topic of discussion in this post, to handle all the
automation

The code for this series is available at [this GitHub repository](https://github.com/dmallubhotla/modular_latex/).
For this post specifically, the final source can be downloaded
[from this tag](https://github.com/dmallubhotla/modular_latex/releases/tag/part2), or be browsed directly in GitHub
[at this commit](https://github.com/dmallubhotla/modular_latex/tree/9a6ec8bd498297abfe84c46155366cc08d7448f8).

## Setting up `make`

There are a million great tutorials on how to actually use `make`, so I'll just focus on how we get started for this
project. To begin, we'll need to create a new file named `Makefile` in the project root (if you're using Windows,
to create a file without an extension, add a `.` to the end, so you would type `Makefile.` in Explorer. The purpose
of a `Makefile` is to specify all the files that you want to be able to create, what the dependencies are and what
code to run to actually do the file creation. The goal here is going to be paying attention to dependencies, so that
we can automate all of the file creation.

Here's an example of making it work to create the `main.pdf` file:
```mf
# Makefile
main.pdf: main.tex
	latexmk -pdf -dvi- -ps- main.tex
```
This tells `make` how to create the `main.pdf` file. It essentially says
* if we want to create `main.pdf`
* it depends on `main.tex`
* the code to generate `main.pdf` is `latexmk -pdf -dvi- -ps- main.tex`
	* this tells `latexmk` to generate a `.pdf` file, but not to generate a `.dvi` or a `.ps` file

In order to run this, you can open up a command line and run `make main.pdf`, which tells your computer to make the
`main.pdf` file. The best part of using build automation tools is that, by default, nothing will actually get run unless
necessary. If the `main.pdf` file already exists, and is up to date, running `make main.pdf` will return
```
$ make main.pdf
make: 'main.pdf' is up to date.
```
and `latexmk` will never actually run. However, if you update `main.tex`, the next time you run `make main.pdf` it will
notice that the dependency has been changed, and regenerate the PDF file correctly.

You might have noticed that our dependencies are actually wrong! Because we set things up to be modular, there are
actually two `.tex` files that get used. We also probably want to be able to make the PDF for problem 1 on its own.
Let's add those to our makefile:
```mf
# Makefile
main.pdf: main.tex problems/Problem1/Problem1.tex
	latexmk -pdf -dvi- -ps- main.tex

problems/Problem1/Problem1.pdf: problems/Problem1/Problem1.tex
	cd problems/Problem1; latexmk -pdf -dvi- -ps- Problem1.tex
```

Now, we can type `make main.pdf` to create `main.pdf`, or type `make problems/Problem1/Problem1.pdf` to make the PDF
for problem 1. If you update either of the `.tex` files, now `make main.pdf` will know that the main PDF is out of date.

Now, you might notice that we're reusing the exact same `latexmk` command for both of the PDFs. Makefiles can set their
own variables to reuse them:
```mf
# Makefile

# Command for latexmk that creates a PDF only
LATEXMK = latexmk -pdf -dvi- -ps-

main.pdf: main.tex problems/Problem1/Problem1.tex
	$(LATEXMK) main.tex

problems/Problem1/Problem1.pdf: problems/Problem1/Problem1.tex
	cd problems/Problem1; $(LATEXMK) Problem1.tex
```

Now, if we decide that we need to change our LaTeX settings, we only have to edit it in one place. This is a really
important indicator of clean design: if you want to change one thing, you should ideally only need to change it in
one part of your code.

### The one command build

We're still not quite at our goal of being able to build everything in a single step. Having a good definition of
"building everything" can be helpful; in this case, we might except that at the end, we should be able to generate
every PDF file, and copy them over to a specific output directory. Here's a makefile that will do that:

```mf
# Makefile

# Command for latexmk that creates a PDF only
LATEXMK = latexmk -pdf -dvi- -ps-

all_pdfs: main.pdf problems/Problem1/Problem1.pdf
	@echo "Creating docs folder if it doesn't exist"
	mkdir -p ./docs
	find . -path ./docs -prune -o -name "*.pdf" -exec cp {} docs \;

.PHONY: all_pdfs

main.pdf: main.tex problems/Problem1/Problem1.tex
	$(LATEXMK) main.tex

problems/Problem1/Problem1.pdf: problems/Problem1/Problem1.tex
	cd problems/Problem1; $(LATEXMK) Problem1.tex
```
There are a few important new things we've added here. The first is that there's a new target named `all_pdfs`.
`mkdir -p ./docs` will create a folder named `docs` if one doesn't already exist. Then, the `find` command will copy
every PDF file that it finds. This is a little bit overkill for what we're doing, because we only have to copy over two
PDF files. However, when we start adding additional problems, we'll want to automatically include those in the `docs`
folder. In order to run this command, you can just type `make all_pdfs`.

Another interesting point is that `all_pdfs` depends on the other PDF files already in the makefile.
This is a really nice part about using Makefiles. Make will check every dependency, and all subdependencies, and
regenerate files as needed. Try it out! Change the text in `Problem1.tex`, and run `make all_pdfs`. If you open up the
files in the `docs` folder, both of the PDF files will include the new text. You can immediately see how this can save
time. Instead of having to go to each `.tex` file and separately generate PDFs, all of your PDFs are automatically put
in a convenient output folder.

We're also using `.PHONY`. This tells `make` that `all_pdfs` isn't actually a real file. Normally, `make` checks to
see if a file exists with the name of whatever command gets run. However, we're never actually generating a file
named `all_pdfs`. It's not necessary, but just to let our Makefile know, we add it to the `.PHONY` list.

Finally, I deliberately put `all_pdfs` above every other target (comments and variables don't count). In your Makefile,
the first target is used as a special default target. If you just type `make` at the command line, it will run that
first target. This means that the only command you need to generate all of your PDFs from your TeX files is `make`.

### Getting ready for adding a second problem

There are quite a few inefficiencies you might spot in the makefile as it is now. If we add a new problem, we'll have
to edit it in multiple places in the makefile. This goes against our clean design indicator. There are a lot of ways
we can fix this, but here's the way I like to approach it
```mf
# Makefile

# This is the list of the different directories for each problem
SUBFILE_NAMES = Problem1
SUBFILE_DIRECTORIES = $(addprefix problems/, $(addsuffix /, $(SUBFILE_NAMES)))
SUBFILE_PDFS =   $(join $(SUBFILE_DIRECTORIES), $(addsuffix .pdf, $(SUBFILE_NAMES)))
SUBFILE_TEXS = $(SUBFILE_PDFS:.pdf=.tex)

# Command for latexmk that creates a PDF only
LATEXMK = latexmk -pdf -dvi- -ps-

all_pdfs: main.pdf $(SUBFILE_PDFS)
	@echo "Creating docs folder if it doesn't exist"
	mkdir -p ./docs
	find . -path ./docs -prune -o -name "*.pdf" -exec cp {} docs \;

.PHONY: all_pdfs

# main.pdf is special because it depends on all of the .tex subfiles
main.pdf: main.tex $(SUBFILE_TEXS)
	$(LATEXMK) main.tex

# Default for PDF files is that they only depend on their corresponding .tex file
%.pdf: %.tex
	cd $(<D); $(LATEXMK) $(<F)
```
I'll leave some of the makefile syntax as an exercise to figure out. Essentially, we're defining a series of variables
that hold all of the various problem files in them, by adding prefixes or suffixes to strings. For example,
`SUBFILE_PDFS` currently is a list with one entry, `problems/Problem1/Problem1.pdf`. At the top, the `SUBFILE_NAMES`
variable is a list of all of the subfile directory names. If we changed that line to `SUBFILE_NAMES = Problem1 Problem2`,
then `SUBFILES_PDFS` would become `problems/Problem1/Problem1.pdf problems/Problem2/Problem2.pdf`. We'll do this next
time. Notice that that would automatically update the dependencies of `all_pdfs` for us, without any extra work. Also
notice that it would tell us that `main.pdf` would have its dependencies updated as well. This means that `make` will be
smart enough to check every `.tex` file to see if `main.pdf` is out of date.

In the last post, I mentioned how I liked to use a consistent naming convention. This is why.
By using the same naming convention for each problem, it makes it a lot easier to automatically make lists of the
various files involved. It's possible to automatically find all of the files, but I like things to be stated a bit more
explicitly.

As you may have noticed, makefiles can start to look a little bit complex. This is okay though. The complexity doesn't
grow quickly beyond a certain point, and once you write your makefile, you only need to update it whenever you start
adding new files. If you're just doing things like actually working on physics and writing your `.tex` files, then you
can simply call `make`, and PDFs will automatically get put in a special directory. I like the ability to put all of
the relatively messy dependency stuff into one place, that way I never have to deal with anything.

Notice also that `make` is a safe tool. As long as you don't put anything destructive in your actual commands, `make`
doesn't really conflict with any other programs. My typical workflow is to use `make` only when I'm updating external
files, or when I'm ready to finalise things. If I'm just typing new text in an editor like TexStudio, then I'll use
PDF viewers in TexStudio (and I configure TexStudio to run the same `latexmk` command). `make` is also idempotent. If
your dependencies are specified correctly, then calling `make` multiple times should only calculate an expensive operation
once. On each run afterwards, `make` can tell that things are up to date, and won't re-run things. This mechanism can
serve in a pinch as a sort of caching mechanism, although I suggest only using makefiles for building final code or
documents.

Next time, we'll really take advantage of our makefile by seeing what happens when we start to introduce non-TeX files.