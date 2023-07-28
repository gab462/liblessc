struct cell {
	int has_bomb;
	int revealed;
	int flagged;
	int neighbors;
};

char cell_char(struct cell cell);
