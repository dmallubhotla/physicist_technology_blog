---
layout: post
title: Automating Mathematica
series: "Modular LaTeX with make"
category: tutorial
tags: mathematica latex make
---

Imagine you generate a figure in a Mathematica notebook to insert into a PDF. Imagine needing to change the image and
update our PDF. You would need to re-run your Mathematica code, then re-run LaTeX. This is the sort of nightmarish
scenario that never needs to happen again.

We're going to be adding a new dependency to our series
* [Mathematica](https://www.wolfram.com/mathematica/), for doing math and computing things

The code for this series is available at [this GitHub repository](https://github.com/dmallubhotla/modular_latex/).
For this post specifically, the final source can be downloaded
[from this tag](https://github.com/dmallubhotla/modular_latex/releases/tag/part3), or be browsed directly in GitHub
[at this commit](https://github.com/dmallubhotla/modular_latex/tree/43c9efc1c2da1541adb01c2af1237ff83ef06c56).

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

Mathematica packages can either use the `.m` extension or the `.wl` extension. I believe `.m` is more standard, but also
conflicts with Matlab files, which also use `.m`. As a result, I prefer to use `.wl` file extensions for Mathematica
packages. The quickest way to run a Mathematica package as a script via the command line is to use `wolframscript`,
which is installed alongside Mathematica. To call it for a particular script, you could call `wolframscript -f script.wl`.

## Back to our situation

In this series, we've been looking at a hypothetical homework set about the expression $$x^2$$. Let's say our second
homework problem is the following:

{:start="2"}
1. Draw a graph of $$x^2$$ over the range $$-10 \leq x \leq 10$$.

### Setting up the files for the second problem

The first thing to do is to create a new `.tex` file for the separate problem. Next to the `problems/Problem1` directory,
we'll create a `problems/Problem2` directory as well, and create a placeholder `Problem2.tex` file:
```tex
% Problem2.tex
\documentclass[../../main.tex]{subfiles}

\begin{document}

\section{Problem 2}
The graph will go here.

\end{document}
```

In order to include this into our main PDF file, we just need to add the reference to the second problem into `main.tex`:
```tex
\subfile{problems/Problem1/Problem1}
% adding this line
\subfile{problems/Problem2/Problem2}

```

Finally, to make sure that our build knows that the main PDF depends on `Problem2.tex`, we'll add it to our makefile:
```mf
# Add Problem2 to this line, and the rest of the
# makefile will automatically pick up the .tex dependency
SUBFILE_NAMES = Problem1 Problem2
```

### Creating our package

We just want a Mathematica script to plot $$x^2$$ over the desired range. Here's a short Mathematica package that makes
a plot, and exports it to an images folder within the `problems/Problem2` directory. I'll save it as
`QuadraticFigureScript.wl`:
```wl
(* QuadraticFigureScript.wl *)
BeginPackage["QuadraticFigureScript`"];

(* Automatically gets the current directory, which should be problems/Problem2 *)
currentDirectory = DirectoryName[
	FileNameJoin[{
		Directory[],
		$ScriptCommandLine[[1]]
	}]
];
(* Gets the name of the output file, problems/Problem2/images/quadraticFigure.jpg *)
figureFilename = FileNameJoin[{
	currentDirectory, "images/quadraticFigure.jpg"
}];

Export[figureFilename,
	Plot[x^2, {x, -10, 10}]
];

EndPackage[];
```

This is a new source file, which creates a generated file `problems/Problem2/images/quadraticFigure.jpg`. The dependency
chain looks like this: `Problem2.pdf` uses the image file, so it depends on `problems/Problem2/images/quadraticFigure.jpg`.
The image file `quadraticFigure.jpg` depends on `QuadraticFigureScript.wl`. We need to add these to the makefile.
Additionally, we need to make sure that `main.pdf` is aware of the image file dependency.

There are a couple good ways of making sure that the makefile knows that both the individual problem PDF and the main
PDF are both aware of the image file dependency. The first is to have `main.pdf` depend on the individual problem PDFs
directly, which automatically would handle all of the dependencies (drawing the dependency tree is a good way of seeing
that). However, this isn't semantically true. The way I prefer to do it is to create a list of the extra dependencies
for each of the subfiles. Here's the extra section that needs to be added to `Makefile`:
```mf
{% raw %}
# We add $(Prob2Dependencies) here to add the extra dependencies, as necessary
main.pdf: main.tex $(SUBFILE_TEXS) $(Prob2Dependencies)
	$(LATEXMK) main.tex

# Problem 2
# just to shorten some folder names
Prob2 = problems/Problem2
# this is the list of extra dependencies. If we had multiple figures for
# this problem, or other dependencies they'd go here
Prob2Dependencies = $(Prob2)/images/quadraticFigure.jpg

# Generates our figure
$(Prob2)/images/quadraticFigure.jpg: $(Prob2)/QuadraticFigureScript.wl
	@echo "Creating images folder if it doesn't exist"
	mkdir -p $(Prob2)/images
	wolframscript -f $(Prob2)/QuadraticFigureScript.wl

# This is only necessary to specify that there are extra dependencies for Problem2.pdf
$(Prob2)/Problem2.pdf: $(Prob2)/Problem2.tex $(Prob2Dependencies)
	cd $(<D); $(LATEXMK) $(<F)
{% endraw %}
```

Now, if you type `make`:
1. make goes to the bottom of the dependency tree, and if necessary,
tries to generate `quadraticFigure.jpg` using the Mathematica script
2. `latexmk` generates all of the PDF files
3. All the PDF files are copied to the `docs` folder

It's very helpful to handle all of this in one command!

## Adding the figure to the `.tex` file
We're still not done. We still need to modify `Problem2.tex` to actually include the generated image. There are a couple
subtle points with using images with subfiles, especially in nested directories like I'm using for this project.

Here are the changes for `Problem2.tex`:
```tex
{% raw %}
% Problem2.tex
\documentclass[../../main.tex]{subfiles}

\begin{document}
% We need to add this to tell LaTeX where our images folder is
\graphicspath{{images/}{./problems/Problem2/images/}}

\section{Problem 2}

\begin{figure}[htp]
	\centering
	\includegraphics[width=10cm]{quadraticFigure} % don't need to add .jpg
	\caption{Here's our figure}
\end{figure}

\end{document}
{% endraw %}
```

The `graphicspath` command comes from LaTeX package `graphicsx`, which we need to include in our `main.tex` file. Here's
the complete `main.tex` file.
```tex
% main.tex
\documentclass{article}

\usepackage{subfiles}
\usepackage{graphicx}

\title{Homework}

\begin{document}

\maketitle

\subfile{problems/Problem1/Problem1}
\subfile{problems/Problem2/Problem2}

\end{document}
```

We're done! Now, we can just use `make` to handle the entire process from start to finish, and correctly include this
figure from Mathematica. We can do the whole thing without ever having to muck around with Mathematica notebook. The
best part of this process is that no matter what changes, whether updating any of the three `.tex` files or updating
the Mathematica script, `make` is the only command necessary to handle the entire process.
