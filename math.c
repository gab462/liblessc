#include "math.h"
#include <stdint.h>

// Parabola approximation
float sin(float x)
{
	float direction = x > PI ? -1.0f : 1.0f;

	while (x < -PI || x > PI) // Convert to 1st quadrant
		x += direction * PI * 2;

	float sign = x < 0 ? -1.0f : 1.0f;

	return 4*x/PI - (4*x*x)/(PI*PI) * sign;
}

float cos(float x)
{
	return sin(x - PI*3.0f/2.0f);
}

// https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Approximations_that_depend_on_the_floating_point_representation
float sqrt(float x)
{
	union { float f; uint32_t i; } val = {x};

	val.i = (1 << 29) + (val.i >> 1) - (1 << 22) - 0x4b0d2;

	return val.f;
}
