#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "audio.h"

#define DURATION 2
#define N (SAMPLE_RATE * DURATION)

#define C4 261.63f

int main(void)
{
	int16_t sound[N];

	for (int i = 0; i < N; ++i) {
		float t = (float){ i } / (float){ SAMPLE_RATE }; // in seconds

		float amp = (float){ INT16_MAX } / 4.0f * (sinf(2 * 3.1415f * 8 * t) + 1.0f / 2.0f); // oscilating volume

		enum wave type;

		if (i < N/4)
			type = WAVE_SINE;
		else if (i < 2 * N / 4)
			type = WAVE_SQUARE;
		else if (i < 3 * N / 4)
			type = WAVE_TRIANGLE;
		else
			type = WAVE_SAW;

		sound[i] = wave_sample(C4, t, amp, type);
	}

	write_wav(sound, N, stdout);

	return 0;
}
