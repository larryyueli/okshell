OkShell
=======

OkShell is a command line interface that is designed to be human-friendly. 

With OkShell you never need to remember

    $ grep -lrIZ fred . | xargs -0 rm -f --

and you can just do

    $ ok recursively delete files containing fred

Below is a link to a presentation that tells what OkShell is all about.

[OkShell Introduction](https://docs.google.com/presentation/d/1HG6YCgUMHHSWAYLbdabj1I1z9pmOVZQp5VvIinCIlXA/pub?start=false&loop=false&delayms=3000)

For questions and feedbacks, please email <okshell.official@gmail.com>


How to install
==============

To be added.


How to use
==========

You could be in one of two modes when using OkShell: NORMAL mode or CONFIG
mode. 

When you are in NORMAL mode, you just want to run some command (90% of use
cases). Just type `ok` followed by whatever you want to do. For example,

    $ ok replace "good" with "great" in txt files

When you are in CONFIG mode occasionally, you want to run some configuration
tasks. Just type `ok` twice, followed by some configuration command. For
example

    $ ok ok cloud off

To see a list of the configuration commands, do 

    $ ok ok help

To see this manual, do 

    $ ok help

