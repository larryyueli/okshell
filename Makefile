CC = g++ -std=c++0x
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LDLIBS = -lboost_serialization -lboost_regex -lboost_filesystem -lboost_system -lreadline -lpthread
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

#TEST_OBJS = utils.o
#TEST_OBJS += test_client.o
#TEST_OBJS += asio_client.o
#
#TEST_SERVER_OBJS = utils.o
#TEST_SERVER_OBJS += test_server.o
#TEST_SERVER_OBJS += asio_server.o

default: ok

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ > ./.depend;

include .depend

ok : $(OBJS)
	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@

#test_client : $(TEST_OBJS)
#	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@
#	
#test_server : $(TEST_SERVER_OBJS)
#	$(CC) $(LFLAGS) $^ $(LDLIBS) -o $@

$(OBJS) : %.o : %.cc
	$(CC) $(CFLAGS) $<

#$(TEST_OBJS) : %.o : %.cc
#	$(CC) $(CFLAGS) $<
#	
#$(TEST_SERVER_OBJS) : %.o : %.cc
#	$(CC) $(CFLAGS) $<
	
clean:
	rm *.o ok

co:
	rm *.o

install:
	@cp ok /usr/local/bin/
	$(info cp ok /usr/local/bin/)
	$(info OkShell installed. Type `ok` to get started.)

