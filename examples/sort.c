#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tui.h"

#define WIDTH 80
#define HEIGHT 24

void render(struct tui *tui, int arr[WIDTH]);

int main(void)
{
	char display[WIDTH * HEIGHT];

	struct tui tui = {
		.display = display,
		.width = WIDTH,
		.height = HEIGHT
	};

	srand(time(NULL));

	int arr[WIDTH];

	for (int i = 0; i < WIDTH; ++i) {
		arr[i] = rand() % HEIGHT;
	}

	setup_term();

	render(&tui, arr);

	getchar();

	fill_tui(&tui, ' ');
	refresh_tui(&tui);

	return 0;
}

void render(struct tui *tui, int arr[WIDTH])
{
	fill_tui(tui, ' ');

	for (int y = 0; y < tui->height; ++y) {
		for (int x = 0; x < tui->width; ++x) {
			if (arr[x] >= HEIGHT - y)
				set_char(tui, x, y, '#');
		}
	}

	refresh_tui(tui);
}
