CC := cc
CFLAGS := -std=c99 -Wall -Wextra -Wshadow -pedantic -I. -ggdb
MATH := -lm

all: mines 3d sound

.PHONY: mines
mines: minesweeper

.PHONY: 3d
3d: shapes_ppm shapes_ascii

.PHONY: sound
sound: wave

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

minesweeper: mines/cell.o mines/map.o mines/main.o tui.o
	$(CC) $(CFLAGS) $^ -o $@

shapes_ppm: 3d/ppm.o 3d/scene.o mesh.o canvas.o
	$(CC) $(CFLAGS) $^ -o $@ $(MATH)

shapes_ascii: 3d/ascii.o 3d/scene.o mesh.o canvas.o tui.o
	$(CC) $(CFLAGS) $^ -o $@ $(MATH)

wave: sound/main.o audio.o
	$(CC) $(CFLAGS) $^ -o $@ $(MATH)
