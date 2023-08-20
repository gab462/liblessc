#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //usleep

#include "tui.h"

#define WIDTH 80
#define HEIGHT 24

void init_array(int arr[WIDTH]);

void bubble(struct tui *tui, int arr[WIDTH]);
void selection(struct tui *tui, int arr[WIDTH]);
void insertion(struct tui *tui, int arr[WIDTH]);
void merge(struct tui *tui, int arr[WIDTH]);
void quick(struct tui *tui, int arr[WIDTH]);

int main(void)
{
	char display[WIDTH * HEIGHT];

	struct tui tui = {
		.display = display,
		.width = WIDTH,
		.height = HEIGHT
	};

	int arr[WIDTH];

	srand(time(NULL));

	setup_term();

	init_array(arr);

	//bubble(&tui, arr);
	//selection(&tui, arr);
	insertion(&tui, arr);

	getchar();

	fill_tui(&tui, ' ');
	refresh_tui(&tui);

	return 0;
}

void init_array(int arr[WIDTH])
{
	for (int i = 0; i < WIDTH; ++i) {
		arr[i] = rand() % HEIGHT;
	}
}

void render(struct tui *tui, int arr[WIDTH], int ptr)
{
	fill_tui(tui, ' ');

	for (int y = 0; y < tui->height; ++y) {
		for (int x = 0; x < tui->width; ++x) {
			char c = x == ptr ? '*' : '#';

			if (arr[x] >= tui->height - y)
				set_char(tui, x, y, c);
		}
	}

	refresh_tui(tui);

	usleep(50000);
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubble(struct tui *tui, int arr[WIDTH])
{
	bool swapped;

	do {
		swapped = false;

		for (int i = 1; i < WIDTH; ++i) {
			render(tui, arr, i);

			if (arr[i - 1] > arr[i]) {
				swap(&arr[i - 1], &arr[i]);

				swapped = true;

				render(tui, arr, i);
			}
		}
	} while (swapped);
}

void selection(struct tui *tui, int arr[WIDTH])
{
	for (int i = 0; i < WIDTH - 1; ++i) {
		int min = i;

		for (int j = i + 1; j < WIDTH; ++j) {
			if (arr[j] < arr[min])
				min = j;

			render(tui, arr, j);
		}

		if (min != i)
			swap(&arr[i], &arr[min]);
	}
}

void insertion(struct tui *tui, int arr[WIDTH])
{
	for (int i = 1; i < WIDTH; ++i) {
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; --j) {
			swap(&arr[j], &arr[j - 1]);

			render(tui, arr, j - 1);
		}
	}
}

void merge(struct tui *tui, int arr[WIDTH])
{
}

void quick(struct tui *tui, int arr[WIDTH])
{
}
