CC := cc
CFLAGS := -std=c99 -Wall -Isrc -D_DEFAULT_SOURCE
LDFLAGS := -lm

all: snake mines 3d wave

.PHONY: 3d
3d: shapes_ppm shapes_ascii

snake: examples/snake.c src/tui.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

mines: examples/mines.c src/tui.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

shapes_ppm: examples/3d/ppm.c examples/3d/scene.c src/mesh.c src/canvas.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

shapes_ascii: examples/3d/ascii.c examples/3d/scene.c src/mesh.c src/canvas.c src/tui.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

wave: examples/wave.c src/audio.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm snake mines shapes_ppm shapes_ascii
