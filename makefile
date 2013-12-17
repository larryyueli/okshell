CC = g++ -std=c++0x
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LDLIBS = -lboost_serialization -lboost_regex -lboost_filesystem -lboost_system
VPATH = src
SRCS = $(wildcard src/*.cc)

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

default: ok

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ > ./.depend;

include .depend

ok : $(OBJS)
	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@

$(OBJS) : %.o : %.cc
	$(CC) $(CFLAGS) $<

cloud_populate.o : cloud_populate.cc
	$(CC) $(CFLAGS) $<

cloud_populate : cloud_populate.o common_defs.o keyboard_input.o profile_writer.o utils.o okshell_utils.o command_profile.o
	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm *.o ok

co:
	rm *.o

install:
	@cp ok /usr/local/bin/
	$(info cp ok /usr/local/bin/)
	$(info OkShell installed. Type `ok` to get started.)

