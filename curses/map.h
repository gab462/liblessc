#define MAP_WIDTH 40
#define MAP_HEIGHT 24

struct map {
	struct cell cells[MAP_HEIGHT][MAP_WIDTH];
};

void reset_map(struct map *map);

int valid_coord(int x, int y);

int neighbor_bombs(struct map *map, int x, int y);

int neighbor_flags(struct map *map, int x, int y);

void reveal_bombs(struct map *map);

void reveal_cell(struct map *map, int x, int y);

void reveal_cell_flow(struct map *map, int x, int y);
