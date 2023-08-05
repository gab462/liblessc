CC := cc
CFLAGS := -std=c99 -Wall -Wextra -Wshadow -pedantic -I. -ggdb
MATH := -lm

all: mines shapes

.PHONY: mines
mines: minesweeper

.PHONY: 3d
3d: shapes

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

minesweeper: mines/cell.o mines/map.o mines/main.o tui.o
	$(CC) $(CFLAGS) $^ -o $@

shapes: 3d/main.o mesh.o canvas.o
	$(CC) $(CFLAGS) $^ -o $@ $(MATH)
