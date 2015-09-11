SC=csc
CC=gcc
CXX=g++
CFLAGS=-g -Wall
CXXFLAGS=-g -Wall -std=c++11 -fPIC

UNAME=$(shell uname)
# mingw is very quirky, we have to set PKG_CONFIG_PATH manually
ifeq ($(OS),Windows_NT)
	PKG_CONFIG_PATH=/mingw64/lib/pkgconfig
	LIBS=$(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --static --libs glfw3 glew)
	DLLEXT := .dll
else
	UNAME := $(shell uname -s)
	LIBS=$(shell pkg-config --static --libs glfw3 glew)
	ifeq ($(UNAME),Darwin)
		DLLEXT := .dylib
	endif
	ifeq ($(UNAME),Linux)
		DLLEXT := .so
	endif
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

sdl-ffi$(DLLEXT): sdl-ffi.scm sdl.o
	$(SC) -s sdl-ffi.scm sdl.o -c++ $(LIBS)

## Building Graphics Engine
engine: libplumgraphics$(DLLEXT)

graphics_test: graphics_test.c libplumgraphics$(DLLEXT)
	$(CC) $(CFLAGS) -o graphics_test graphics_test.c -L. -lplumgraphics

libplumgraphics$(DLLEXT): graphics.o libplumloader$(DLLEXT)
	$(CXX) -shared -o libplumgraphics$(DLLEXT) graphics.o $(LIBS) -L. -lplumloader

graphics.o: graphics.cpp graphics.h mesh.h plum_loader.h shader.h *.vert *.frag
	$(CXX) $(CXXFLAGS) -c graphics.cpp shader.h

plum_loader_test: test/plum_loader_test.c libplumloader$(DLLEXT)
	$(CC) $(CFLAGS) -o plum_loader_test test/plum_loader_test.c -L. -lplumloader

libplumloader$(DLLEXT): plum_loader.o model.o mesh.o
	$(CXX) -shared -o libplumloader$(DLLEXT) plum_loader.o model.o mesh.o $(LIBS)

plum_loader.o: plum_loader.cpp plum_loader.h mesh.h
	$(CXX) $(CXXFLAGS) -c plum_loader.cpp plum_loader.h

model.o: model.cpp model.h
	$(CXX) $(CXXFLAGS) -c model.cpp

mesh.o: mesh.cpp mesh.h
	$(CXX) $(CXXFLAGS) -c mesh.cpp
clean:
	rm -rf *.o *$(DLLEXT) *.gch *.dSYM a.out plum graphics graphics_test
