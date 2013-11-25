CC = g++ -std=c++0x
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LDLIBS = -lboost_serialization
VPATH = src

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
OBJS += cloud_matcher.o
OBJS += common_defs.o
OBJS += globals.o
OBJS += keyboard_input.o
OBJS += profile_writer.o
OBJS += user_config.o
OBJS += cloud_sync.o
OBJS += command_profile.o

default: ok

okinit.o : okinit.cc
	$(CC) $(CFLAGS) $<

okinit : okinit.o command_profile.o globals.o
	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@

ok : $(OBJS)
	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@

ok.o : ok.cc
	$(CC) $(CFLAGS) $<

okshell.o : okshell.cc okshell.h
	$(CC) $(CFLAGS) $<

mode_parser.o : mode_parser.cc mode_parser.h
	$(CC) $(CFLAGS) $<

utils.o : utils.cc utils.h 
	$(CC) $(CFLAGS) $<

help_displayer.o : help_displayer.cc help_displayer.h
	$(CC) $(CFLAGS) $<

config_help_displayer.o : config_help_displayer.cc config_help_displayer.h
	$(CC) $(CFLAGS) $<

normal_commander.o : normal_commander.cc normal_commander.h
	$(CC) $(CFLAGS) $<
	
config_commander.o : config_commander.cc config_commander.h
	$(CC) $(CFLAGS) $<

local_matcher.o : local_matcher.cc local_matcher.h
	$(CC) $(CFLAGS) $<

cloud_matcher.o : cloud_matcher.cc cloud_matcher.h
	$(CC) $(CFLAGS) $<

common_defs.o : common_defs.cc common_defs.h
	$(CC) $(CFLAGS) $<

globals.o : globals.cc globals.h
	$(CC) $(CFLAGS) $<

keyboard_input.o : keyboard_input.cc keyboard_input.h
	$(CC) $(CFLAGS) $<

profile_writer.o : profile_writer.cc profile_writer.h
	$(CC) $(CFLAGS) $<

user_config.o : user_config.cc user_config.h
	$(CC) $(CFLAGS) $<

cloud_sync.o : cloud_sync.cc cloud_sync.h
	$(CC) $(CFLAGS) $<

command_profile.o : command_profile.cc command_profile.h
	$(CC) $(CFLAGS) $<

clean:
	rm *.o ok

co:
	rm *.o

install:
	cp ok /usr/local/bin/

