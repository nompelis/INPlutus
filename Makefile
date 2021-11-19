###### Compilers
CC = gcc
COPTS = -g -Wall -fPIC -O0
CXX = g++
CXXOPTS = -g -Wall -fPIC -O0

###### libraries
LIBS = -lm 

###### debugging switches
DEBUG += -D   _DEBUG_
DEBUG += -D NO_DEBUG2_


all:
	$(CC) -c $(DEBUG) $(COPTS) inp.c
	$(CC)    $(DEBUG) $(COPTS) main.c \
            inp.o $(LIBS)

clean:
	rm -f *.o *.a a.out

