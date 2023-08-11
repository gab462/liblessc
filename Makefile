CC := cc
CFLAGS := -std=c99 -Wall -Wextra -Wshadow -pedantic -I. -ggdb
LDFLAGS := -static
MATH := -lm

all: snake mines 3d sound

.PHONY: ssnake
ssnake: snake

.PHONY: mines
mines: minesweeper

.PHONY: 3d
3d: shapes_ppm shapes_ascii

.PHONY: sound
sound: wave

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

snake: ssnake/main.o tui.o
	$(CC) $^ -o $@ $(LDFLAGS)

minesweeper: mines/cell.o mines/map.o mines/main.o tui.o
	$(CC) $^ -o $@ $(LDFLAGS)

shapes_ppm: 3d/ppm.o 3d/scene.o mesh.o canvas.o
	$(CC) $^ -o $@ $(LDFLAGS) $(MATH)

shapes_ascii: 3d/ascii.o 3d/scene.o mesh.o canvas.o tui.o
	$(CC) $^ -o $@ $(LDFLAGS) $(MATH)

wave: sound/main.o audio.o
	$(CC) $^ -o $@ $(LDFLAGS) $(MATH)
