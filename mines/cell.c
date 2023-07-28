#include "cell.h"

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
