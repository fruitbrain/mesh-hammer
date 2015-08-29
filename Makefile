SC=csc
CC=g++
CXXFLAGS=-Wall -c -std=c++11

UNAME=$(shell uname)
# mingw is very quirky, we have to set PKG_CONFIG_PATH manually
ifeq ($(UNAME),MINGW64_NT-10.0)
#For manual compiling:
#LDFLAGS=-mwindows -lSDL2main -lSDL2 C:/msys64/mingw64/lib/libglfw3.a C:/msys64/mingw64/lib/libglew32.a -lopengl32
PKG_CONFIG_PATH=/mingw64/lib/pkgconfig
LDFLAGS=$(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --static --libs sdl2 glfw3 glew)
else
LDFLAGS=$(shell pkg-config --static --libs sdl2 glfw3 glew)
endif

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
engine: main.o plum_loader.o
	$(CC) -o main main.o plum_loader.o $(LDFLAGS)

main.o: main.cpp shader.h plum_loader.h shader
	$(CC) $(CXXFLAGS) main.cpp shader.h

plum_loader.o: plum_loader.cpp plum_loader.h
	$(CC) $(CXXFLAGS) plum_loader.cpp plum_loader.h

shader: shader.vert shader.frag lamp.frag

clean:
	rm -f *.o *.gch plum main
