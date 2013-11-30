CC = g++ -std=c++0x
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LDLIBS = -lboost_serialization -lboost_regex
VPATH = src

OBJS =
OBJS += ok.o
OBJS += okshell.o
OBJS += globals.o
OBJS += logger.o
OBJS += mode_parser.o
OBJS += utils.o
OBJS += okshell_utils.o
OBJS += help_displayer.o
OBJS += config_help_displayer.o
OBJS += normal_commander.o
OBJS += config_commander.o
OBJS += local_matcher.o
OBJS += cloud_matcher.o
OBJS += common_defs.o
OBJS += keyboard_input.o
OBJS += profile_writer.o
OBJS += cloud_sync.o
OBJS += command_profile.o
OBJS += config.o

default: ok install

cloud_populate.o : cloud_populate.cc
	$(CC) $(CFLAGS) $<

cloud_populate : cloud_populate.o common_defs.o globals.o profile_writer.o keyboard_input.o logger.o utils.o command_profile.o
	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@

okinit.o : okinit.cc
	$(CC) $(CFLAGS) $<

okinit : okinit.o command_profile.o globals.o config.o
	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@

ok : $(OBJS)
	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@

ok.o : ok.cc
	$(CC) $(CFLAGS) $<

okshell.o : okshell.cc okshell.h logger.h
	$(CC) $(CFLAGS) $<

globals.o : globals.cc globals.h
	$(CC) $(CFLAGS) $<

mode_parser.o : mode_parser.cc mode_parser.h
	$(CC) $(CFLAGS) $<

utils.o : utils.cc utils.h 
	$(CC) $(CFLAGS) $<

okshell_utils.o : okshell_utils.cc okshell_utils.h 
	$(CC) $(CFLAGS) $<

help_displayer.o : help_displayer.cc help_displayer.h
	$(CC) $(CFLAGS) $<

config_help_displayer.o : config_help_displayer.cc config_help_displayer.h
	$(CC) $(CFLAGS) $<

normal_commander.o : normal_commander.cc normal_commander.h logger.h
	$(CC) $(CFLAGS) $<
	
config_commander.o : config_commander.cc config_commander.h logger.h
	$(CC) $(CFLAGS) $<

local_matcher.o : local_matcher.cc local_matcher.h logger.h
	$(CC) $(CFLAGS) $<

cloud_matcher.o : cloud_matcher.cc cloud_matcher.h
	$(CC) $(CFLAGS) $<

common_defs.o : common_defs.cc common_defs.h
	$(CC) $(CFLAGS) $<

keyboard_input.o : keyboard_input.cc keyboard_input.h logger.h
	$(CC) $(CFLAGS) $<

profile_writer.o : profile_writer.cc profile_writer.h
	$(CC) $(CFLAGS) $<

cloud_sync.o : cloud_sync.cc cloud_sync.h
	$(CC) $(CFLAGS) $<

command_profile.o : command_profile.cc command_profile.h
	$(CC) $(CFLAGS) $<

logger.o : logger.cc logger.h
	$(CC) $(CFLAGS) $<

config.o : config.cc config.h
	$(CC) $(CFLAGS) $<

clean:
	rm *.o ok

co:
	rm *.o

install:
	cp ok /usr/local/bin/

