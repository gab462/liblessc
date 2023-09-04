CC := cc
CFLAGS := -std=c99 -Wall -Isrc -D_DEFAULT_SOURCE
LDFLAGS := -lm

all: snake mines 3d wave sort

.PHONY: 3d
3d: shapes_ppm shapes_ascii

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

snake: examples/snake.o src/tui.o
	$(CC) $^ -o $@ $(LDFLAGS)

mines: examples/mines.o src/tui.o
	$(CC) $^ -o $@ $(LDFLAGS)

shapes_ppm: examples/3d/ppm.o examples/3d/scene.o src/mesh.o src/canvas.o
	$(CC) $^ -o $@ $(LDFLAGS)

shapes_ascii: examples/3d/ascii.o examples/3d/scene.o src/mesh.o src/canvas.o src/tui.o
	$(CC) $^ -o $@ $(LDFLAGS)

wave: examples/wave.o src/audio.o
	$(CC) $^ -o $@ $(LDFLAGS)

sort: examples/sort.o src/tui.o
	$(CC) $^ -o $@ $(LDFLAGS)
