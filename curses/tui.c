#include "tui.h"
#include <unistd.h>
#include <termios.h>
#include <stdio.h>

void setup_term(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void clear_screen(struct tui *tui, char c)
{
	for (int i = 0; i < tui->width * tui->height; ++i) {
		tui->display[i] = c;
	}
}

void set_char(struct tui *tui, int x, int y, char c)
{
	tui->display[y * tui->width + x] = c;
}

void show_screen(struct tui *tui)
{
	for (int i = 0; i < tui->height; ++i) {
		fwrite(&tui->display[i * tui->width], tui->width, 1, stdout);
		fputc('\n', stdout);
	}

	printf("\x1b[%dD", tui->width);
	printf("\x1b[%dA", tui->height);
}

void restore_term(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
