SC=csc
CC=g++
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
	$(CC) $(CXXFLAGS) -c sdl.cpp

## Building Graphics Engine
engine: main.o plum_loader.o
	$(CC) -o main main.o plum_loader.o $(LIBS)

main.o: main.cpp shader.h plum_loader.h shader
	$(CC) $(CXXFLAGS) -c main.cpp shader.h

plum_loader.so: plum_loader.o
	$(CC) -shared -o plum_loader.so plum_loader.o $(LIBS)

plum_loader.o: plum_loader.cpp plum_loader.h
	$(CC) $(CXXFLAGS) -c plum_loader.cpp plum_loader.h

shader: shader.vert shader.frag lamp.frag

clean:
	rm -f *.o *.so *.gch a.out plum main
