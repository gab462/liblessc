#include <stdint.h>
#include <unistd.h>

#include "random.h"

// https://www.reedbeta.com/blog/hash-functions-for-gpu-rendering/
uint32_t pgc(uint32_t input)
{
	uint32_t state = input * 747796405u + 2891336453u;
	uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
	return (word >> 22u) ^ word;
}

float random(void)
{
	static uint32_t seed = 0;

	// set pid as pseudo-random seed on first execution
	if (seed == 0)
		seed = getpid();

	seed = pgc(seed);

	return ((float) seed) / ((float) UINT32_MAX);
}
