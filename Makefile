CC := cc
COMMONCFLAGS := -std=c99 -Wall -Wextra -Wshadow -pedantic -I.
CFLAGS := $(COMMONCFLAGS) -ggdb
WASMCFLAGS := $(COMMONCFLAGS) --target=wasm32 -O2 --no-standard-libraries -fno-builtin
WASMLDFLAGS := -Wl,--export-all -Wl,--no-entry

all: mines wasm3d

.PHONY: mines
mines: minesweeper

.PHONY: wasm3d
wasm3d: index.wasm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

minesweeper: mines/cell.o mines/map.o mines/random.o mines/main.o tui.o
	$(CC) $(CFLAGS) $^ -o $@

index.wasm: $(wildcard wasm3d/*.c) math.c mesh.c canvas.c
	clang $(WASMCFLAGS) $^ -o index.wasm $(WASMLDFLAGS)
