CC = g++ -std=c++0x
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
VPATH=src

OBJS =
OBJS += ok.o
OBJS += okshell.o
OBJS += mode_parser.o
OBJS += utils.o
OBJS += help_displayer.o
OBJS += config_help_displayer.o
OBJS += normal_commander.o
OBJS += config_commander.o
OBJS += local_matcher.o
OBJS += common_defs.o
OBJS += globals.o

default: ok

ok : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

ok.o : ok.cpp
	$(CC) $(CFLAGS) $<

okshell.o : okshell.cpp okshell.hpp
	$(CC) $(CFLAGS) $<

mode_parser.o : mode_parser.cpp mode_parser.hpp
	$(CC) $(CFLAGS) $<

utils.o : utils.cpp utils.hpp 
	$(CC) $(CFLAGS) $<

help_displayer.o : help_displayer.cpp help_displayer.hpp
	$(CC) $(CFLAGS) $<

config_help_displayer.o : config_help_displayer.cpp config_help_displayer.hpp
	$(CC) $(CFLAGS) $<

normal_commander.o : normal_commander.cpp normal_commander.hpp
	$(CC) $(CFLAGS) $<
	
config_commander.o : config_commander.cpp config_commander.hpp
	$(CC) $(CFLAGS) $<

local_matcher.o : local_matcher.cpp local_matcher.hpp
	$(CC) $(CFLAGS) $<

common_defs.o : common_defs.cpp common_defs.hpp
	$(CC) $(CFLAGS) $<

globals.o : globals.cpp globals.hpp
	$(CC) $(CFLAGS) $<

clean:
	rm *.o ok

co:
	rm *.o

install:
	cp ok /usr/local/bin/

