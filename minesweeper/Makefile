CC := cc
CFLAGS := -std=c99 -Wall -Wextra -Wshadow -pedantic -ggdb
OBJS := cell.o map.o random.o tui.o main.o
TARGET := a.out

$(TARGET): $(OBJS)
	$(CC) $^ -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm $(OBJS) $(TARGET)
