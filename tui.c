#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <string.h> // memset
#include <stdlib.h> // atexit

#include "tui.h"

void restore_term(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void setup_term(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	atexit(restore_term);
}

void fill_tui(struct tui *tui, char c)
{
	memset(tui->display, c, tui->width * tui->height);
}

void set_char(struct tui *tui, int x, int y, char c)
{
	tui->display[y * tui->width + x] = c;
}

void refresh_tui(struct tui *tui)
{
	for (int i = 0; i < tui->height; ++i) {
		fwrite(&tui->display[i * tui->width], tui->width, 1, stdout);
		fputc('\n', stdout);
	}

	printf("\x1b[%dD", tui->width);
	printf("\x1b[%dA", tui->height);
}
