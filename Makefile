SC=csc
CC=gcc
CXX=g++
CFLAGS=-g -Wall
CXXFLAGS=-g -Wall -std=c++11 -fPIC

UNAME=$(shell uname)
# mingw is very quirky, we have to set PKG_CONFIG_PATH manually
ifeq ($(UNAME),MINGW64_NT-10.0)
#For manual compiling:
#LIBS=-mwindows -lSDL2main -lSDL2 C:/msys64/mingw64/lib/libglfw3.a C:/msys64/mingw64/lib/libglew32.a -lopengl32
PKG_CONFIG_PATH=/mingw64/lib/pkgconfig
LIBS=$(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --static --libs glfw3 glew)
else
LIBS=$(shell pkg-config --static --libs glfw3 glew)
endif

EXE=plum
SCFLAGS=-o $(EXE) -c++ $(LIBS)

all: plum

plum: plum.o sdl-ffi.o sdl.o
	$(SC) plum.o sdl-ffi.o sdl.o $(SCFLAGS)

plum.o: plum.scm
	$(SC) -c plum.scm -c++

sdl-ffi.o: sdl-ffi.scm
	$(SC) -c sdl-ffi.scm -c++

sdl-ffi.so: sdl-ffi.scm sdl.o
	$(SC) -s sdl-ffi.scm sdl.o -c++ $(LIBS)

sdl.o: sdl.cpp
	$(CXX) $(CXXFLAGS) -c sdl.cpp

## Building Graphics Engine
engine: main.o plum_loader.o
	$(CXX) $(CXXFLAGS) -o main main.o plum_loader.o $(LIBS)

main.o: main.cpp shader.h plum_loader.h shader
	$(CXX) $(CXXFLAGS) -c main.cpp shader.h

plum_loader_test: test/plum_loader_test.c libplumloader.so
	$(CC) $(CFLAGS) -o plum_loader_test test/plum_loader_test.c -L. -lplumloader

libplumloader.so: plum_loader.o
	$(CXX) $(CXXFLAGS)-shared -o libplumloader.so plum_loader.o $(LIBS)

plum_loader.o: plum_loader.cpp plum_loader.h
	$(CXX) $(CXXFLAGS) -c plum_loader.cpp plum_loader.h

shader: shader.vert shader.frag lamp.frag

clean:
	rm -f *.o *.so *.gch a.out plum main plum_loader_test
