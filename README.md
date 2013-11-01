OkShell
=======

OkShell is a command line interface that is designed to be human-friendly. 

With OkShell you never need to remember

    $ grep -lrIZ fred . | xargs -0 rm -f --

and you can just do

    $ ok recursively delete files containing fred


How to install
==============

To be added.


How to use
==========

< __OkShell User Manual__ >

You could be in one of two modes when using OkShell: NORMAL mode or CONFIG mode. 

When you are in NORMAL mode, you just want to run some command (90% of use cases). Just do

    $ ok whatever you want to do

For example,

    $ ok replace "good" with "great" in all txt files

When you are in CONFIG mode occasionally, you want to run some administrative tasks. Just type `ok` twice

    $ ok ok some administrative commands

To see a list of the administrative commands, do 

    $ ok ok help

To see this manual, do 

    $ ok help

< __End of OkShell User Manual__ >

