// 2d and 3d software rendering

struct canvas {
	uint32_t *pixels;
	int width;
	int height;
};

void fill_canvas(struct canvas *canvas, uint32_t color);

void set_pixel(struct canvas *canvas, int x, int y, uint32_t color);

void draw_line(struct canvas *canvas, int x1, int y1, int x2, int y2, uint32_t color);

void draw_mesh(struct canvas *canvas, struct mesh mesh, float offset[3], float scale, float distance, uint32_t color);

void render_ppm(struct canvas *canvas, FILE *stream);

void render_ascii(struct canvas *canvas, FILE *stream, bool with_newlines);
