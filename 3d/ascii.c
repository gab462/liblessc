#define _DEFAULT_SOURCE // M_PI, fmemopen

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h> //usleep

#include "mesh.h"
#include "canvas.h"
#include "tui.h"
#include "scene.h"

#define WIDTH 80
#define HEIGHT 40

int main(void)
{
	uint32_t pixels[WIDTH * HEIGHT];

	struct canvas canvas = { pixels, WIDTH, HEIGHT };

	char display[WIDTH * HEIGHT / 2];

	struct tui tui = {
		.display = display,
		.width = WIDTH,
		.height = HEIGHT / 2
	};

	setup_term();

	float angle = 0.0f;

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

	fill_tui(&tui, ' ');
	refresh_tui(&tui);

	return 0;
}
