CC = gcc
UNAME_S := $(shell uname -s)

CFLAGS = -O2 -ftree-vectorize -fno-semantic-interposition -pipe -s -flto
WARNINGS = -Wall -Wextra -Wwrite-strings

ifeq ($(OS),Windows_NT)
	LINKS = -Lwindows/lib -lmingw32 -lSDL2main -lSDL2	
	INCLUDES = -Iwindows/include
	DISABLE_CONSOLE = -mwindows
	DYN_EXC = bin/SDL2.dll
else
	LINKS = -lSDL2main -lSDL2
endif

RELEASE = $(CFLAGS) $(WARNINGS) $(LINKS) $(INCLUDES) $(DISABLE_CONSOLE)
DEBUG = $(WARNINGS) $(LINKS) $(INCLUDES) -g

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

OUTPUT = bin/release
DEBUG_OUTPUT = bin/debug

debug: $(DEBUG_OUTPUT) $(DYN_EXC)
release: $(OUTPUT) $(DYN_EXC)

$(OUTPUT): $(SRC)
	$(CC) $^ -o $@ $(RELEASE)

$(DEBUG_OUTPUT): $(OBJ)
	$(CC) $^ -o $@ $(DEBUG)

$(DYN_EXC):
	cp windows/bin/SDL2.dll bin/

obj/%.o: src/%.c
	$(CC) $^ -c -o $@ $(DEBUG)

run: debug 
	$(DEBUG_OUTPUT)