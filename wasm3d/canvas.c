#include "mesh.h"
#include <stdint.h>
#include "canvas.h"

void clear_screen(struct canvas *canvas, uint32_t color)
{
	for (int i = 0; i < canvas->width * canvas->height; ++i) {
		canvas->pixels[i] = color;
	}
}

void set_pixel(struct canvas *canvas, int x, int y, uint32_t color)
{
	canvas->pixels[y * canvas->width + x] = color;
}

// https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
void draw_line(struct canvas *canvas, int x1, int y1, int x2, int y2, uint32_t color)
{
	float dx = x2 - x1;
	float dy = y2 - y1;

	float adx = dx < 0 ? -dx : dx;
	float ady = dy < 0 ? -dy : dy;

	float step = adx > ady ? adx : ady;

	dx /= step;
	dy /= step;

	float x = x1;
	float y = y1;

	for (int i = 1; i <= step; ++i) {
		set_pixel(canvas, x, y, color);

		x += dx;
		y += dy;
	}
}

void draw_mesh(struct canvas *canvas, struct mesh mesh, uint32_t color)
{
	float center[3] = { canvas->width / 2, canvas->height / 2, 0.0f };

	offset_mesh(&mesh, center);

	for (int i = 0; i < mesh.n_edges; ++i) {
		int *edge = mesh.edges[i];

		float *va = mesh.vertices[edge[0]];
		float *vb = mesh.vertices[edge[1]];

		draw_line(canvas, va[0], va[1], vb[0], vb[1], color);
	}
}
