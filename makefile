CC = g++ -std=c++0x
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LDLIBS = -lboost_serialization -lboost_regex -lboost_filesystem -lboost_system
VPATH = src

OBJS =
OBJS += ok.o
OBJS += okshell.o
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
OBJS += initializer.o

default: ok install

demo_install : demo_install.cc
	$(CC) $(LFLAGS) $^ -o $@

cloud_populate.o : cloud_populate.cc
	$(CC) $(CFLAGS) $<

cloud_populate : cloud_populate.o common_defs.o profile_writer.o keyboard_input.o utils.o command_profile.o okshell_utils.o
	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@

okinit.o : okinit.cc globals.h
	$(CC) $(CFLAGS) $<

okinit : okinit.o command_profile.o globals.o config.o
	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@

ok : $(OBJS)
	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@

ok.o : ok.cc globals.h
	$(CC) $(CFLAGS) $<

okshell.o : okshell.cc okshell.h logger.h globals.h
	$(CC) $(CFLAGS) $<

mode_parser.o : mode_parser.cc mode_parser.h globals.h
	$(CC) $(CFLAGS) $<

utils.o : utils.cc utils.h 
	$(CC) $(CFLAGS) $<

okshell_utils.o : okshell_utils.cc okshell_utils.h globals.h
	$(CC) $(CFLAGS) $<

help_displayer.o : help_displayer.cc help_displayer.h globals.h
	$(CC) $(CFLAGS) $<

config_help_displayer.o : config_help_displayer.cc config_help_displayer.h globals.h
	$(CC) $(CFLAGS) $<

normal_commander.o : normal_commander.cc normal_commander.h logger.h globals.h
	$(CC) $(CFLAGS) $<
	
config_commander.o : config_commander.cc config_commander.h logger.h globals.h
	$(CC) $(CFLAGS) $<

local_matcher.o : local_matcher.cc local_matcher.h logger.h globals.h
	$(CC) $(CFLAGS) $<

cloud_matcher.o : cloud_matcher.cc cloud_matcher.h globals.h
	$(CC) $(CFLAGS) $<

common_defs.o : common_defs.cc common_defs.h globals.h
	$(CC) $(CFLAGS) $<

keyboard_input.o : keyboard_input.cc keyboard_input.h logger.h globals.h
	$(CC) $(CFLAGS) $<

profile_writer.o : profile_writer.cc profile_writer.h globals.h
	$(CC) $(CFLAGS) $<

cloud_sync.o : cloud_sync.cc cloud_sync.h globals.h
	$(CC) $(CFLAGS) $<

command_profile.o : command_profile.cc command_profile.h globals.h
	$(CC) $(CFLAGS) $<

config.o : config.cc config.h globals.h
	$(CC) $(CFLAGS) $<

initializer.o : initializer.cc initializer.h logger.h globals.h
	$(CC) $(CFLAGS) $<

clean:
	rm *.o ok

co:
	rm *.o

install:
	cp ok /usr/local/bin/

