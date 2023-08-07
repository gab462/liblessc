#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "audio.h"

#define DURATION 2
#define N (SAMPLE_RATE * DURATION)

int main(void)
{
	int16_t sound[N];

	float volume = INT16_MAX / 4;

	for (int i = 0; i < N; ++i) {
		float t = (float){ i } / (float){ SAMPLE_RATE }; // in seconds

		if (i < N/2)
			sound[i] = sine_sample(261.63f, t, volume);
		else
			sound[i] = sine_sample(440.0f, t, volume);
	}

	write_wav(sound, N, stdout);

	return 0;
}
