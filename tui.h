// TUI rendering

struct tui {
	char *display;
	int width;
	int height;
};

void setup_term(void);

void fill_tui(struct tui *tui, char c);

void set_char(struct tui *tui, int x, int y, char c);

void refresh_tui(struct tui *tui);

//void restore_term(void); // called automatically
