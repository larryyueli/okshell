What is OkShell
===============

OkShell is a command line interface that is designed to be human-friendly. 

With OkShell you never need to remember

    $ find . -type f -name \*.txt -exec sed -i 's/Alice/Bob/g' {} \;

and you can just do

    $ ok replace Alice with Bob in all txt files

Below is a link to a presentation that tells what OkShell is all about.

[OkShell Introduction](https://docs.google.com/presentation/d/1HG6YCgUMHHSWAYLbdabj1I1z9pmOVZQp5VvIinCIlXA/pub?start=false&loop=false&delayms=3000)

For questions and feedbacks, please email <okshell.official@gmail.com>.


How to Install
==============

The installation of OkShell is currently in "Pro Mode", i.e., you need to
compile it from the source code and know what you are doing. It will become
more convenient in future releases. Below is the instruction:

Supported operating systems: Major Linux distributions, e.g., Ubuntu, RedHat, etc.

1. Make sure you have the following packages installed on your computer.
	- g++ version 4.6 or above (recommanded package: build-essential)
	- libboost-dev
	- libboost-serialization-dev
	- libboost-regex-dev
	- libboost-filesystem-dev
	- libboost-system-dev

2. Run `make`

3. Run `sudo make install`


How to Use
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


Compatibility Alert
===================

OkShell is currently at early development stage and there is no guarantee of
backward compatibility across the early versions. This means that when you
upgrade to a newer version of OkShell, it might not work with the config and
profile files of the older version. However, we will try to reduce this type of
inconvenience as much as possible.

__[ Copyright (c) 2013 Larry Yueli Zhang ]__

