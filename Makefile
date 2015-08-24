SC=csc
CC=g++
CXXFLAGS=-Wall -c -std=c++11
#LDFLAGS=-mwindows -lSDL2main -lSDL2 C:/msys64/mingw64/lib/libglfw3.a C:/msys64/mingw64/lib/libglew32.a -lopengl32
LDFLAGS=`pkg-config --static --libs sdl2 glfw3 glew`
EXE=plum
SCFLAGS=-o $(EXE) -c++ $(LDFLAGS)

all: plum

plum: plum.o sdl-ffi.o sdl.o
	$(SC) plum.o sdl-ffi.o sdl.o $(SCFLAGS)

plum.o: plum.scm
	$(SC) -c plum.scm -c++

sdl-ffi.o: sdl-ffi.scm
	$(SC) -c sdl-ffi.scm -c++

sdl-ffi.so: sdl-ffi.scm sdl.o
	$(SC) -s sdl-ffi.scm sdl.o -c++ $(LDFLAGS)

sdl.o: sdl.cpp
	$(CC) $(CXXFLAGS) sdl.cpp

## Building Graphics Engine
engine: main.o
	$(CC) -o main main.o $(LDFLAGS)

main.o: main.cpp shader.h
	$(CC) $(CXXFLAGS) main.cpp shader.h

clean:
	rm -f *.o *.gch plum main
