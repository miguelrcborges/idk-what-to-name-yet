CC = clang
CFLAGS = -O2 -ftree-vectorize -fno-semantic-interposition -pipe -s -flto $$(sdl2-config --cflags)
LINKS = $$(sdl2-config --libs)
WARNINGS = -Wall -Wextra -Wwrite-strings
OBJDIR = obj
BINDIR = bin

RELEASE = $(CFLAGS) $(WARNINGS)
DEBUG = $(WARNINGS) -Og -g

.PHONY: debug release run clean

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
	$(CC) $^ -o $@ $(RELEASE) $(LINKS)

$(DEBUG_OUTPUT): $(OBJ)
	$(CC) $^ -o $@ $(DEBUG) $(LINKS)

obj/%.o: src/%.c
	$(CC) $^ -c -o $@ $(DEBUG)

run: debug 
	$(DEBUG_OUTPUT)

test:
	echo $(echo a)

clean:
	rm -rf obj bin