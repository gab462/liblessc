#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "mesh.h"
#include "canvas.h"

void fill_canvas(struct canvas *canvas, uint32_t color)
{
	for (int i = 0; i < canvas->width * canvas->height; ++i) {
		canvas->pixels[i] = color;
	}
}

void set_pixel(struct canvas *canvas, int x, int y, uint32_t color)
{
	if (x < 0 || x >= canvas->width || y < 0 || y >= canvas->height)
		return;

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

void offset_mesh(struct mesh *mesh, float offset[3])
{
	for (int i = 0; i < mesh->n_vertices; ++i)
		for (int j = 0; j < 3; ++j)
			mesh->vertices[i][j] += offset[j];
}

void scale_mesh(struct mesh *mesh, float scale)
{
	for (int i = 0; i < mesh->n_vertices; ++i)
		for (int j = 0; j < 3; ++j)
			mesh->vertices[i][j] *= scale;
}

void project_mesh(struct mesh *mesh, float distance)
{
	for (int i = 0; i < mesh->n_vertices; ++i) {
		float *v = mesh->vertices[i];

		float proj = 1.0f / (distance - v[2]);

		v[0] *= proj;
		v[1] *= proj;
	}
}

void draw_mesh(struct canvas *canvas, struct mesh mesh, float offset[3], float scale, float distance, uint32_t color)
{
	// Offset only z at first to keep center at (0,0)
	offset_mesh(&mesh, (float[3]){ 0.0f, 0.0f, offset[2] });

	project_mesh(&mesh, distance);
	scale_mesh(&mesh, scale);

	offset_mesh(&mesh, (float[3]){ offset[0], offset[1], 0.0f });
	offset_mesh(&mesh, (float[3]){ canvas->width / 2, canvas->height / 2, 0.0f });

	for (int i = 0; i < mesh.n_edges; ++i) {
		int *edge = mesh.edges[i];

		float *va = mesh.vertices[edge[0]];
		float *vb = mesh.vertices[edge[1]];

		draw_line(canvas, va[0], va[1], vb[0], vb[1], color);
	}
}

void render_ppm(struct canvas *canvas, FILE *stream)
{
	fprintf(stream, "P6\n%d %d 255\n", canvas->width, canvas->height);

	for (int i = 0; i < canvas->width * canvas->height; ++i) {
		uint32_t pixel = canvas->pixels[i];

		uint8_t data[3] = {
			pixel & 0x0000FF,
			(pixel & 0x00FF00) >> 8,
			(pixel & 0xFF0000) >> 8 * 2
		};

		fwrite(data, sizeof(data), 1, stream);
	}
}

void render_ascii(struct canvas *canvas, FILE *stream, bool with_newlines)
{
	// TODO: grayscale

	char mapping[2][2] = {
		{ ' ', '_' },
		{ '^', '#' }
	};

	for (int y = 0; y < canvas->height / 2; ++y) {
		for (int x = 0; x < canvas->width; ++x) {
			int top = canvas->pixels[2 * y * canvas->width + x] > 0xFF000000;
			int bottom = canvas->pixels[(2 * y + 1) * canvas->width + x] > 0xFF000000;

			fputc(mapping[top][bottom], stream);
		}

		if (with_newlines)
			fputc('\n', stream);
	}
}
