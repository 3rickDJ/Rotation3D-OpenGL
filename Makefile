CC =g++
CFLAGS =-g -Wall
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

BINDIR=bin
BIN = $(BINDIR)/main
LIBS =-lGL -lglut -lGLU

all:$(BIN)

release: CFLAGS=-Wall -DNDEBUG
release: clean
release: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(BIN)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	-rm -r $(BINDIR)/* $(OBJ)/*
