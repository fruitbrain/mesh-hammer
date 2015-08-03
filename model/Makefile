CFLAGS=-c -g -Wall -std=c++11
LIB=-lmingw32 -lglew32 -lSDL2main -lSDL2 -lSDL2_test -lOpenGL32

all: main

main: main.o display.o mesh.o obj_loader.o shader.o stb_image.o texture.o
	g++ -o main display.o mesh.o obj_loader.o shader.o stb_image.o texture.o main.o $(LIB)

main.o: main.cpp
	g++ $(CFLAGS) main.cpp

display.o: display.cpp
	g++ $(CFLAGS) display.cpp

mesh.o: mesh.cpp
	g++ $(CFLAGS) mesh.cpp

obj_loader.o: obj_loader.cpp
	g++ $(CFLAGS) obj_loader.cpp

shader.o: shader.cpp
	g++ $(CFLAGS) shader.cpp

stb_image.o: stb_image.c
	g++ $(CFLAGS) stb_image.c

texture.o: texture.cpp
	g++ $(CFLAGS) texture.cpp

clean:
	rm -r *.o main
