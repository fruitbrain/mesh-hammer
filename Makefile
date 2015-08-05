SC=csc
CC=g++
CXXFLAGS=-Wall -c -std=c++11
LDFLAGS=-lmingw32 -lSDL2main -lSDL2
EXE=plum
SCFLAGS=-o $(EXE) -c++ $(LDFLAGS)

all: plum

plum: plum.o sdl-ffi.o sdl.o
	$(SC) plum.o sdl-ffi.o sdl.o $(SCFLAGS)

plum.o:
	$(SC) -c plum.scm -c++

sdl-ffi.o:
	$(SC) -c sdl-ffi.scm -c++

sdl-ffi.so: sdl-ffi.scm sdl.o
	$(SC) -s sdl-ffi.scm sdl.o -c++ $(LDFLAGS) 

sdl.o: sdl.cpp
	$(CC) $(CXXFLAGS) sdl.cpp

clean:
	rm -f *.o plum
