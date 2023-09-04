#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //usleep

#include "tui.h"

#define WIDTH 80
#define HEIGHT 24

static int arr[WIDTH];

struct tui tui;

void init_array(void);
void travel(void);

void bubble(void);
void insertion(void);
void selection(void);
void merge(void);
void quick(void);

int main(void)
{
	char display[WIDTH * HEIGHT];

	tui = (struct tui){
		.display = display,
		.width = WIDTH,
		.height = HEIGHT
	};

	srand(time(NULL));

	setup_term();

	void (*algorithms[])(void) = { insertion, selection, bubble };

	for (int i = 0; i < sizeof(algorithms) / sizeof(algorithms[0]); ++i) {
		init_array();

		usleep(2000000);

		algorithms[i]();

		travel();

		usleep(2000000);
	}

	fill_tui(&tui, ' ');
	refresh_tui(&tui);

	return 0;
}

void render(int ptr)
{
	fill_tui(&tui, ' ');

	for (int y = 0; y < tui.height; ++y) {
		for (int x = 0; x < tui.width; ++x) {
			char c = x == ptr ? '*' : '#';

			if (arr[x] >= tui.height - y)
				set_char(&tui, x, y, c);
		}
	}

	refresh_tui(&tui);

	usleep(50000);
}

void init_array(void)
{
	for (int i = 0; i < WIDTH; ++i) {
		arr[i] = rand() % HEIGHT;

		render(i);
	}
}

void travel(void)
{
	for (int i = 0; i < WIDTH; ++i) {
		render(i);
	}
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubble(void)
{
	bool swapped;

	do {
		swapped = false;

		for (int i = 1; i < WIDTH; ++i) {
			if (arr[i - 1] > arr[i]) {
				swap(&arr[i - 1], &arr[i]);

				swapped = true;
			}

			render(i);
		}
	} while (swapped);
}

void insertion(void)
{
	for (int i = 1; i < WIDTH; ++i) {
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; --j) {
			swap(&arr[j], &arr[j - 1]);

			render(j - 1);
		}
	}
}

void selection(void)
{
	for (int i = 0; i < WIDTH - 1; ++i) {
		int min = i;

		for (int j = i + 1; j < WIDTH; ++j) {
			if (arr[j] < arr[min])
				min = j;

			render(j);
		}

		if (min != i)
			swap(&arr[i], &arr[min]);
	}
}

void merge(void)
{
	// TODO
}

void quick(void)
{
	// TODO
}
