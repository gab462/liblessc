CC := clang
LD := wasm-ld
CFLAGS := -std=c99 -Wall -Wextra -Wshadow -pedantic --target=wasm32 -O2 --no-standard-libraries -fno-builtin
LDFLAGS := --export-all --no-entry
OBJS := wasm.o math.o mesh.o canvas.o
TARGET := index.wasm

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm $(OBJS) $(TARGET)
