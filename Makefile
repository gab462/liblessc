CC := cc
CFLAGS := -std=c99 -Wall -I. -D_DEFAULT_SOURCE
LDFLAGS := -lm

all: snake mines 3d sound

.PHONY: ssnake
ssnake: snake

.PHONY: mines
mines: minesweeper

.PHONY: 3d
3d: shapes_ppm shapes_ascii

.PHONY: sound
sound: wave

snake: ssnake/main.c tui.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

minesweeper: mines/cell.c mines/map.c mines/main.c tui.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

shapes_ppm: 3d/ppm.c 3d/scene.c mesh.c canvas.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

shapes_ascii: 3d/ascii.c 3d/scene.c mesh.c canvas.c tui.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

wave: sound/main.c audio.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm snake minesweeper shapes_ppm shapes_ascii
