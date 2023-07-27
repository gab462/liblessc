#include <stdint.h>

#include "cell.h"
#include "map.h"
#include "random.h"

void reset_map(struct map *map)
{
	struct cell *cells = &map->cells[0][0];

	for (int i = 0; i < MAP_HEIGHT * MAP_WIDTH; ++i) {
		struct cell *cell = &cells[i];

		if (random() < 0.15f)
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
