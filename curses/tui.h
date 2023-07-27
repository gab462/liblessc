struct tui {
	char *display;
	int width;
	int height;
};

void setup_term(void);

void clear_screen(struct tui *tui, char c);

void set_char(struct tui *tui, int x, int y, char c);

void show_screen(struct tui *tui);

void restore_term(void);
