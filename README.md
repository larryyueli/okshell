What is OkShell
===============

OkShell is a command line interface for humans. 

With OkShell you never need to remember

    $ find . -type f -name \*.txt -exec sed -i 's/Alice/Bob/g' {} \;

instead you can simply do

    $ ok replace Alice with Bob in all txt files

Below is a link to a presentation that explains what OkShell is all about.

[OkShell Introduction](https://docs.google.com/presentation/d/1HG6YCgUMHHSWAYLbdabj1I1z9pmOVZQp5VvIinCIlXA/pub?start=false&loop=false&delayms=3000)

For questions and feedbacks, please email <okshell.official@gmail.com>.


How to Install
==============

The installation of OkShell is currently in "pro mode", i.e., you need to
compile it from the source code and know what you are doing. It will become
more convenient for general users in future releases.

Currently supported operating systems: Most Linux distributions, e.g., Ubuntu,
RedHat, etc.

To install:

1. Download source code of OkShell by (if you have Git installed)

		$ git clone https://github.com/larryyueli/okshell.git

	or download the zip file or tar.gz file.

2. Make sure you have the following packages installed on your computer.

	- g++ version 4.6 or above (recommanded package: build-essential)
	- libboost-dev
	- libboost-serialization-dev
	- libboost-regex-dev
	- libboost-filesystem-dev
	- libboost-system-dev

3. Under `okshell` directory, run `make`

4. Run `sudo make install`


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


___Copyright (c) 2013 Larry Yueli Zhang___

