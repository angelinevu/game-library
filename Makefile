#Angeline Vu, 03/03/2024, CS302-001, Program 3
#Makefile: automates linking and compiling of files

OBJS = main.o game.o client.o tree.o
SOURCES = main.cpp game.cpp client.cpp tree.cpp
DEPS = game.h BST.h
TARGET = game

FLAGS = -g -std=c++17

CC = g++

.PHONY = clean zip

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(FLAGS)

clean:
	rm -f $(OBJS) $(TARGET)

zip:
	zip program3.zip README.md Makefile client.cpp game.cpp game.h main.cpp tree.cpp tree.h
