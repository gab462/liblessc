CC := cc
CFLAGS := -std=c99 -Wall -Wextra -Wshadow -pedantic -I. -ggdb

all: mines wasm3d

.PHONY: mines
mines: minesweeper

minesweeper: $(wildcard mines/*.c) tui.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

WASMCFLAGS := -std=c99 -Wall -Wextra -Wshadow -pedantic --target=wasm32 -O2 --no-standard-libraries -fno-builtin -I.
WASMLDFLAGS := -Wl,--export-all -Wl,--no-entry

.PHONY: wasm3d
wasm3d: index.wasm

index.wasm: $(wildcard wasm3d/*.c) math.c mesh.c canvas.c
	clang $(WASMCFLAGS) $^ -o index.wasm $(WASMLDFLAGS)
