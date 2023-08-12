#include <stdbool.h>
#include <stddef.h>
#include <stdio.h> // getchar
#include <stdlib.h> // srand
#include <time.h> // random seed

#include "tui.h"

#define MAX_SIZE 32

struct snake {
	int body[MAX_SIZE][2];
	int head;
	int tail;
	int size;
};

struct map {
	int width;
	int height;
	int food_pos[2];
};

bool pos_equal(int a[2], int b[2])
{
	return a[0] == b[0] && a[1] == b[1];
}

void relocate_food(struct map *map)
{
	map->food_pos[0] = rand() % map->width;
	map->food_pos[1] = rand() % map->height;
}

// take modulus and if negative, subtract from max
int wrap(int x, int max)
{
	return x % max + (x % max < 0) * max;
}

void slither(struct snake *snake, int offset[2], struct map *map)
{
	int *prev = snake->body[snake->head];

	snake->head = (snake->head + 1) % MAX_SIZE;

	snake->body[snake->head][0] = wrap(prev[0] + offset[0], map->width);
	snake->body[snake->head][1] = wrap(prev[1] + offset[1], map->height);

	if (pos_equal(snake->body[snake->head], map->food_pos) && snake->size < MAX_SIZE) {
		++snake->size;
		relocate_food(map);
	} else {
		snake->tail = (snake->tail + 1) % MAX_SIZE;
	}
}

void update_game(char ch, struct snake *snake, struct map *map)
{
	static int offset[2] = { 1, 0 }; // keeps state

	switch (ch) {
		case 'w':
			offset[0] = 0;
			offset[1] = -1;
			break;
		case 'a':
			offset[0] = -1;
			offset[1] = 0;
			break;
		case 's':
			offset[0] = 0;
			offset[1] = 1;
			break;
		case 'd':
			offset[0] = 1;
			offset[1] = 0;
			break;
		case ' ':
			offset[0] = 0;
			offset[1] = 0;
			break;
		default:
			break;
	};

	slither(snake, offset, map);
}

void render_game(struct tui *tui, struct snake *snake, struct map *map)
{
	fill_tui(tui, ' ');

	set_char(tui, map->food_pos[0], map->food_pos[1], '*');

	for (int i = 0; i < snake->size; ++i) {
		int idx = (snake->tail + i) % MAX_SIZE;
		int *pos = snake->body[idx];

		set_char(tui, pos[0], pos[1], '#');
	}

	refresh_tui(tui);
}

#define WIDTH 80
#define HEIGHT 24

int main(void)
{
	char display[WIDTH * HEIGHT];

	struct tui tui = {
		.display = display,
		.width = WIDTH,
		.height = HEIGHT
	};

	struct snake snake = { .size = 1 };

	struct map map = {
		.width = WIDTH,
		.height = HEIGHT,
		.food_pos = { 1, 0 }
	};

	char ch = 'd';

	srand(time(NULL));

	setup_term();

	do {
		update_game(ch, &snake, &map);
		render_game(&tui, &snake, &map);

		ch = getchar();
	} while (ch != 'q');

	fill_tui(&tui, ' ');
	refresh_tui(&tui);

	return 0;
}
