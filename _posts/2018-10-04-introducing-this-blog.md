---
layout: post
title: Introduction to this blog
series: Introduction
---

This is going to be the start of a few series of tutorials about how I think physics projects can be structured, 
to make computing easier and more useful.

# Test of highlighting
Here's an example of some syntax highlighting:
```tex
\documentclass[11pt]{article}

\begin{document}
\renewcommand{\onlyinsubfile}[1]{}
\renewcommand{\notinsubfile}[1]{#1}

\maketitle

\tableofcontents

\subfile{notes/DrudeTheory/DrudeTheory}

\subfile{notes/DerivingThomasFermi/DerivingThomasFermi}

\subfile{notes/ReducingLindhard/ReducingLindhard}

\subfile{notes/LindhardExplicitParts/LindhardExplicitParts}

\subfile{notes/QubitRelaxation/QubitRelaxation}

\newpage
\section{todos}
\listoftodos

\end{document}
```
 
#### Why is this important?
* Reproducibility is important
* Physicist time should be considered expensive
* Testability and reviewability are important

#### What will this discuss?

