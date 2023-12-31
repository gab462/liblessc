#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h> //usleep
#include <math.h>

#include "mesh.h"
#include "canvas.h"
#include "tui.h"

#define WIDTH 80
#define HEIGHT 40

#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0xFF000000

void render(struct canvas *canvas, float angle)
{
	struct mesh cube = {
		.n_vertices = 8,
		.n_edges = 12,
		.vertices = (float[][3]) {
			{ -0.5f, -0.5f, -0.5f },
			{  0.5f, -0.5f, -0.5f },
			{  0.5f,  0.5f, -0.5f },
			{ -0.5f,  0.5f, -0.5f },
			{ -0.5f, -0.5f,  0.5f },
			{  0.5f, -0.5f,  0.5f },
			{  0.5f,  0.5f,  0.5f },
			{ -0.5f,  0.5f,  0.5f }
		},
		.edges = (int[][2]) {
			{ 0, 1 }, { 0, 4 }, { 4, 5 },
			{ 1, 2 }, { 1, 5 }, { 5, 6 },
			{ 2, 3 }, { 2, 6 }, { 6, 7 },
			{ 3, 0 }, { 3, 7 }, { 7, 4 }
		}
	};

	// FIXME: not centered
	struct mesh pyramid = {
		.n_vertices = 4,
		.n_edges = 6,
		.vertices = (float[][3]) {
			{ -0.5f, 0.5f, -0.5f },
			{  0.5f, 0.5f, -0.5f },
			{  0.0f, 0.5f, sqrtf(3.0f / 4.0f) - 0.5f },
			{  0.0f, -sqrtf(2.0f / 3.0f) + 0.5f, sqrtf(1.0f / 12.0f) - 0.5f }
		},
		.edges = (int[][2]) {
			{ 0, 1 }, { 1, 2 }, { 2, 0 },
			{ 0, 3 }, { 1, 3 }, { 2, 3 }
		}
	};

	float h = canvas->height;

	float pyramid_offset[3] = { h * 0.25f, 0.0f, 0.0f };
	float cube_offset[3] = { - h * 0.25f, 0.0f, 0.0f };

	rotate_mesh(&cube, angle, AXIS_X);
	rotate_mesh(&cube, angle, AXIS_Y);
	rotate_mesh(&cube, angle, AXIS_Z);

	rotate_mesh(&pyramid, angle, AXIS_X);
	rotate_mesh(&pyramid, angle, AXIS_Y);
	rotate_mesh(&pyramid, angle, AXIS_Z);

	// Translate
	rotate_point(cube_offset, angle, AXIS_Z);
	rotate_point(pyramid_offset, angle, AXIS_Z);

	fill_canvas(canvas, COLOR_BLACK);

	draw_mesh(canvas, cube, cube_offset, h * 0.7f, 2.0f, COLOR_WHITE);

	draw_mesh(canvas, pyramid, pyramid_offset, h * 0.7f, 2.0f, COLOR_WHITE);
}

int main(void)
{
	uint32_t pixels[WIDTH * HEIGHT];

	struct canvas canvas = { pixels, WIDTH, HEIGHT };

	char display[WIDTH * HEIGHT / 2];

	struct tui tui = { display, WIDTH, HEIGHT / 2 };

	setup_term();

	float angle = 0.0f;

	// TODO: exit gracefully
	while (true) {
		fill_tui(&tui, ' ');

		render(&canvas, angle);

		FILE *screen = fmemopen(tui.display, tui.width * tui.height, "w");
		render_ascii(&canvas, screen, false);
		fclose(screen);

		refresh_tui(&tui);

		usleep(100000);

		angle += 0.1f;
	}

	return 0;
}
