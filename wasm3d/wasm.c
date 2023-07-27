#include <stdint.h>
#include "mesh.h"
#include "canvas.h"
#include "math.h"

#define WIDTH 320
#define HEIGHT 160
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0xFF000000

// TODO: distance projection
uint32_t *render(float timestamp)
{
	static uint32_t pixels[WIDTH * HEIGHT];

	struct canvas canvas = { pixels, WIDTH, HEIGHT };

	static float previous = 0.0f;
	static float angle = 0.0f;

	float dt = timestamp - previous;

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
		.vertices = (float[][3]){
			{ -0.5f, 0.5f, -0.5f },
			{  0.5f, 0.5f, -0.5f },
			{  0.0f, 0.5f, sqrt(3.0f / 4.0f) - 0.5f },
			{  0.0f, -sqrt(2.0f / 3.0f) + 0.5f, sqrt(1.0f / 12.0f) - 0.5f }
		},
		.edges = (int[][2]) {
			{ 0, 1 }, { 1, 2 }, { 2, 0 },
			{ 0, 3 }, { 1, 3 }, { 2, 3 }
		}
	};

	angle += dt / 1000.f;

	if (angle > PI)
		angle -= PI * 2;

	clear_screen(&canvas, COLOR_BLACK);

	rotate_mesh_x(&cube, angle);
	rotate_mesh_y(&cube, angle);
	rotate_mesh_z(&cube, angle);
	zoom_mesh(&cube, 50.0f);
	offset_mesh(&cube, (float[3]){ -50.0f, 0.0f, 0.0f });

	draw_mesh(&canvas, cube, COLOR_WHITE);

	rotate_mesh_x(&pyramid, angle);
	rotate_mesh_y(&pyramid, angle);
	rotate_mesh_z(&pyramid, angle);
	zoom_mesh(&pyramid, 50.0f);
	offset_mesh(&pyramid, (float[3]){ 50.0f, 0.0f, 0.0f });

	draw_mesh(&canvas, pyramid, COLOR_WHITE);

	previous = timestamp;

	return canvas.pixels;
}

// FIXME: disable optimization
void *memcpy(void *dst, void *src, int n)
{
	char *d = dst;
	char *s = src;

	while (n--) *d++ = *s++;

	return dst;
}
