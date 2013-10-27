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

default: ok

ok : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

ok.o : ok.cpp okshell.o
	$(CC) $(CFLAGS) $<

okshell.o : okshell.cpp okshell.hpp
	$(CC) $(CFLAGS) $<

mode_parser.o : mode_parser.cpp mode_parser.hpp utils.o
	$(CC) $(CFLAGS) $<

utils.o : utils.cpp utils.hpp 
	$(CC) $(CFLAGS) $<

clean:
	rm *.o ok

co:
	rm *.o

