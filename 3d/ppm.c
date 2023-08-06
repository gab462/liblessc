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

	render_ppm(&canvas, stdout);

	return 0;
}
