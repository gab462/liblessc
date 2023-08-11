#include <stdint.h>
#include <stddef.h>
#include <stdio.h> // getchar
#include <stdlib.h> // srand
#include <time.h> // random seed

#include "tui.h"
#include "player.h"
#include "cell.h"
#include "map.h"

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
