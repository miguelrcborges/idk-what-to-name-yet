CC = clang
RELEASE = -O2 -ftree-vectorize -fno-semantic-interposition -pipe -s -flto 
CFLAGS = $$(pkg-config sdl2 SDL2_ttf --cflags)
LINKS = $$(pkg-config sdl2 SDL2_ttf --libs)
WARNINGS = -Wall -Wextra -Wwrite-strings
DEBUG = $(WARNINGS) -Og -g
OBJDIR = obj
BINDIR = bin


.PHONY: debug release run clean

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

OUTPUT = bin/release
DEBUG_OUTPUT = bin/debug

debug: $(OBJDIR) $(BINDIR) $(DEBUG_OUTPUT)
release: $(BINDIR) $(OUTPUT)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OUTPUT): $(SRC)
	$(CC) $^ -o $@ $(RELEASE) $(CFLAGS) $(LINKS)

$(DEBUG_OUTPUT): $(OBJ)
	$(CC) $^ -o $@ $(DEBUG) $(LINKS)

obj/%.o: src/%.c
	$(CC) $^ -c -o $@ $(DEBUG) $(CFLAGS)

run: debug 
	cd bin && ./debug

test:
	echo $(echo a)

clean:
	rm -rf obj bin/release bin/debug
