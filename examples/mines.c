#include <stdint.h>
#include <stddef.h>
#include <stdio.h> // getchar
#include <stdlib.h> // srand, rand
#include <time.h> // random seed

#include "tui.h"

struct player {
	int x;
	int y;
};

struct cell {
	int has_bomb;
	int revealed;
	int flagged;
	int neighbors;
};

#define MAP_WIDTH 40
#define MAP_HEIGHT 24

struct map {
	struct cell cells[MAP_HEIGHT][MAP_WIDTH];
};

void reset_map(struct map *map);

void update_game(struct player *player, struct map *map, char c);

void render_game(struct tui *tui, struct player *player, struct map *map);

int main(void)
{
	char display[MAP_WIDTH * 2 * MAP_HEIGHT];

	struct tui tui = {
		.display = display,
		.width = MAP_WIDTH * 2,
		.height = MAP_HEIGHT
	};

	struct player player = {0};
	struct map map;
	char ch;

	srand(time(NULL));

	reset_map(&map);

	setup_term();

	do {
		render_game(&tui, &player, &map);

		ch = getchar();

		update_game(&player, &map, ch);
	} while (ch != 'q');

	fill_tui(&tui, ' ');
	refresh_tui(&tui);

	return 0;
}

char cell_char(struct cell cell)
{
	if (cell.revealed) {
		if (cell.has_bomb)
			return '*';
		else if (cell.neighbors == 0)
			return ' ';
		else
			return '0' + cell.neighbors;
	} else if (cell.flagged) {
		return '#';
	} else {
		return '-';
	}
}

void reset_map(struct map *map)
{
	struct cell *cells = &map->cells[0][0];

	for (int i = 0; i < MAP_HEIGHT * MAP_WIDTH; ++i) {
		struct cell *cell = &cells[i];

		if (rand() % 100 < 15)
			cell->has_bomb = 1;
		else
			cell->has_bomb = 0;

		cell->revealed = 0;
		cell->flagged = 0;
		cell->neighbors = 0;
	}
}

int valid_coord(int x, int y)
{
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
		return 0;
	else
		return 1;
}

int neighbor_bombs(struct map *map, int x, int y)
{
	int bombs = 0;

	for (int i = y - 1; i <= y + 1; ++i) {
		for (int j = x - 1; j <= x + 1; ++j) {
			if (!valid_coord(j, i))
				continue;

			struct cell cell = map->cells[i][j];

			if (cell.has_bomb)
				++bombs;
		}
	}

	return bombs;
}

int neighbor_flags(struct map *map, int x, int y)
{
	int flags = 0;

	for (int i = y - 1; i <= y + 1; ++i) {
		for (int j = x - 1; j <= x + 1; ++j) {
			if (!valid_coord(j, i))
				continue;

			struct cell cell = map->cells[i][j];

			if (cell.flagged)
				++flags;
		}
	}

	return flags;
}

void reveal_bombs(struct map *map)
{
	struct cell *cells = &map->cells[0][0];

	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i)
		if (cells[i].has_bomb)
			cells[i].revealed = 1;
}

void reveal_cell_flow(struct map *map, int x, int y);

void reveal_cell(struct map *map, int x, int y)
{
	struct cell *cell = &map->cells[y][x];

	if (cell->revealed || cell->flagged)
		return;

	cell->revealed = 1;

	if (cell->has_bomb) {
		reveal_bombs(map);

		return;
	}

	cell->neighbors = neighbor_bombs(map, x, y);

	if (cell->neighbors == 0)
		reveal_cell_flow(map, x, y);
}

void reveal_cell_flow(struct map *map, int x, int y)
{
	struct cell cell = map->cells[y][x];

	if (!cell.revealed)
		return;

	if (cell.neighbors > neighbor_flags(map, x, y))
		return;

	for (int i = y - 1; i <= y + 1; ++i) {
		for (int j = x - 1; j <= x + 1; ++j) {
			if (!valid_coord(j, i))
				continue;

			reveal_cell(map, j, i);
		}
	}
}

int clamp(int from, int to, int x)
{
	return x < from ? from : x > to ? to : x;
}

void update_game(struct player *player, struct map *map, char c)
{
	switch (c) {
	case 'w':
		player->y = clamp(0, MAP_HEIGHT, player->y - 1);
		break;
	case 'a':
		player->x = clamp(0, MAP_WIDTH, player->x - 1);
		break;
	case 's':
		player->y = clamp(0, MAP_HEIGHT, player->y + 1);
		break;
	case 'd':
		player->x = clamp(0, MAP_WIDTH, player->x + 1);
		break;
	case 'j':
		if (map->cells[player->y][player->x].revealed)
			reveal_cell_flow(map, player->x, player->y);
		else
			reveal_cell(map, player->x, player->y);
		break;
	case 'k':
		map->cells[player->y][player->x].flagged = 1;
		break;
	case 'u':
		map->cells[player->y][player->x].flagged = 0;
		break;
	case 'r':
		reset_map(map);
		break;
	default:
		break;
	}
}

void render_game(struct tui *tui, struct player *player, struct map *map)
{
	fill_tui(tui, ' ');

	for (int y = 0; y < MAP_HEIGHT; ++y) {
		for (int x = 0; x < MAP_WIDTH; ++x) {
			struct cell cell = map->cells[y][x];

			set_char(tui, x * 2, y, cell_char(cell));
		}
	}

	set_char(tui, player->x * 2, player->y, 'x');

	refresh_tui(tui);
}
