#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "mesh.h"
#include "canvas.h"
#include "scene.h"

#define WIDTH 320
#define HEIGHT 160

int main(void)
{
	uint32_t pixels[WIDTH * HEIGHT];

	struct canvas canvas = { pixels, WIDTH, HEIGHT };

	render(&canvas, 3.1415f / 4.0f);

	FILE* file = fopen("1.ppm", "wb+");

	render_ppm(&canvas, file);

	fclose(file);

	return 0;
}
