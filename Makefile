SC=csc
CC=g++
CXXFLAGS=-Wall -c -std=c++11
LDFLAGS=-lmingw32 -lSDL2main -lSDL2
SCFLAGS=-o plum -c++ $(LDFLAGS)

all: plum

plum: plum.scm sdl.o
	$(SC) plum.scm sdl.o $(SCFLAGS)

sdl.o: sdl.cpp
	$(CC) $(CXXFLAGS) sdl.cpp

clean:
	rm -f *.o plum
