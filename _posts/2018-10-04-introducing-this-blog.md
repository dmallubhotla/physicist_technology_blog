---
layout: post
title: Introduction to this blog
usereadtime: true
excerpt_separator: "\n\n\n"
---

This is going to be the start of a few series of tutorials about how I think physics projects can be structured, 
to make computing easier and more useful. Ultimately, I hope it ends up a helpful collection of resources people 
can use to try to bring their physics computing out from the 90s. I haven't seen physicists talking a lot about 
software or workflows, and I think it's something everyone could stand to improve.


# Why is this important?
I think there are some critical attributes any good physics project should exhibit:
## Reproducibility
Science relies on reproducibility, especially for handling data. If two scientists measure the same phenomena, they 
should get the same results. I think something similar should apply for our computing resources as well. If two 
people start from scratch on new computers, and decide to test the exact same raw data, they should be able to get 
the exact same results. This shouldn't be limited to data analysis either; it should be possible to start from 
`.tex` files, raw data and scripts and generate figures based on the data and `.pdf` files using those figures. 

A good computing setup should help reproducibility by _automating_ all of this. Every step a human has to do is risky.
The best case situation is that someone forgets to execute that step, the worst case is that the human introduces 
errors. Automation makes it easier for new people to join a project and start contributing, by making the software 
simpler to run. Even for a single person, it can be a massive time saver to automate as much as possible.

The goal for this attribute should be to make sure your entire project can start from scratch and generate results 
consistently with a single, easy-to-repeat step. In a software development context, 
[Joel Spolsky refers to this](https://www.joelonsoftware.com/2000/08/09/the-joel-test-12-steps-to-better-code/)
as a one step build, but there's no reason for scientists to not do the same thing. Computers are tools built to handle 
repetitive, boring tasks in deterministic ways, so human beings should try to offload those tasks as much as possible.

## Self-verification
Software always introduces a risk of bugs, and one way to mitigate that risk is to automate testing. It's common
practice to test scientific software, but by automating this process, your code can start to test itself. Some examples 
of testable software situations:
* Someone might create some scripts that perform lots of statistical analysis on some experimental data. To verify
those scripts, they should be run on some test data that has known results. That way, if the scripts have any errors,
the test data should reveal it (this also relies on having robust test data to compare against).
* If trying to numerically calculate something, those numerical calculations should also be done on systems that have 
known analytic results. Then, the scripts handling the numerical estimation can be compared against the analytic values 
to verify whether the program is operating at the expected accuracy / precision.

Note that both of these are simple numerical comparisons! Simple tests like this can be automated. This is awesome, 
because it means that whenever you're editing your code, you can quickly test your code and make sure you didn't 
introduce any new bugs. 

I don't think a full [TDD](https://en.wikipedia.org/wiki/Test-driven_development) approach is necessary for physicists,
but for physicists who write any code, it's important to make sure that code is actually correct! If code never 
gets tested properly, then it's irresponsible to use it for science. This isn't economics; in physics the details matter.
I also don't believe that something counts as getting tested properly if it's only human-tested; humans are unreliable
and don't test in reproducible ways.

## Reviewability
Science doesn't always adapt quickly to new technology; the peer review process has room to improve in terms of 
evaluating software-driven resource. A lot of other people have already talked about the need for scientists to make
data and methods more accessible, so there's little for me to add aobut how open-access journals and open-source 
software make research better.

The other part of making a physics project easy to review is to make it _readable_. Writing code is much easier 
than reading it, as thousands of software developers have already figured out. Making sure that code is readable
and self-contained is one way to alleviate that burden. Even if peer-reviewers aren't taking the time to verify code, 
collaborators should be, so readable code is a way to avoid annoying them.  

Additionally, not only should code be readable; it should also be _accessible_. Even if making a particular project fully 
open-source isn't an option, within a group code needs to stay easily accessible, which is also useful for keeping code
_editable_.

## Editability

This is probably what I hope to discuss the most. All of the above will help with improving the quality of science,
but they'll also help make the lives of scientists easier. Instead of having to dig through Dropbox folders to find a 
script, then figure out out how to run that script to calculate some data, then open up another program to try to 
create a graph, which gets copied and pasted somewhere else for a `.tex` file, a physicist's workflow should just take
one step to recompute everything easily. Then, that physicist should be able to look at easy-to-read code, use tests
to see where the software is having problems, and easily collaborate with someone else to fix it.

Making a project easy to edit means no longer having to fight against a computer, but instead letting the computer handle
things on its own. Keeping things easily editable lets you take a new computer and immediately pick up exactly where 
you left off on the old one.

Not every project needs all of these things, and it's not always easy making a project follow these. I'm hoping that 
I can share some ideas on how to get there though,  