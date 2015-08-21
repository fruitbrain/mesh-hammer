SC=csc
CC=g++
CXXFLAGS=-Wall -c -std=c++11
LDFLAGS=-mwindows -lSDL2main -lSDL2 C:/msys64/mingw64/lib/libglfw3.a C:/msys64/mingw64/lib/libglew32.a -lopengl32
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

## Building Graphics Engine
engine: main.o
	$(CC) -o main main.o $(LDFLAGS)
	
main.o:
	$(CC) $(CXXFLAGS) main.cpp
	
clean:
	rm -f *.o plum main