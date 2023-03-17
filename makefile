CC = gcc
UNAME_S := $(shell uname -s)

CFLAGS = -O2 -ftree-vectorize -fno-semantic-interposition -pipe -s -flto
WARNINGS = -Wall -Wextra -Wwrite-strings
OBJDIR = obj
BINDIR = bin

RELEASE = $(CFLAGS) $(WARNINGS)
DEBUG = $(WARNINGS) -Og -g

.PHONY: debug release run

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

OUTPUT = bin/release
DEBUG_OUTPUT = bin/debug

debug: $(OBJDIR) $(BINDIR) $(DEBUG_OUTPUT) $(DYN_EXC)
release: $(BINDIR) $(OUTPUT) $(DYN_EXC)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OUTPUT): $(SRC)
	$(CC) $^ -o $@ $(RELEASE) $(sdl2-config --libs)

$(DEBUG_OUTPUT): $(OBJ)
	$(CC) $^ -o $@ $(DEBUG) $(sdl2-config --libs)

$(DYN_EXC):
	cp windows/bin/SDL2.dll bin/

obj/%.o: src/%.c
	$(CC) $^ -c -o $@ $(DEBUG) $/sdl2-config --cflags)

run: debug 
	$(DEBUG_OUTPUT)
