CC = g++ -std=c++0x
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
VPATH=src
OBJS = ok.o okshell.o

default: ok

ok : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

ok.o : ok.cpp okshell.o
	$(CC) $(CFLAGS) $<

okshell.o : okshell.cpp okshell.hpp
	$(CC) $(CFLAGS) $<

clean:
	rm *.o ok

