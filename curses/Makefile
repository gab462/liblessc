CC := cc
LD := ld
CFLAGS := -std=c99 -Wall -Wextra -Wshadow -pedantic -ggdb
OBJS := $(wildcard *.c)
TARGET := a.out

$(TARGET): $(OBJS)
	$(CC) $^ -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm $(OBJS) $(TARGET)
