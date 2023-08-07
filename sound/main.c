#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "audio.h"

#define DURATION 2
#define N (SAMPLE_RATE * DURATION)

int main(void)
{
	int16_t sound[N];

	float amp = INT16_MAX / 4;

	for (int i = 0; i < N; ++i) {
		float t = (float){ i } / (float){ SAMPLE_RATE }; // in seconds

		if (i < N/4)
			sound[i] = wave_sample(261.63f, t, amp, WAVE_SINE);
		else if (i < 2 * N / 4)
			sound[i] = wave_sample(261.63f, t, amp, WAVE_SQUARE);
		else if (i < 3 * N / 4)
			sound[i] = wave_sample(261.63f, t, amp, WAVE_TRIANGLE);
		else
			sound[i] = wave_sample(261.63f, t, amp, WAVE_SAW);
	}

	write_wav(sound, N, stdout);

	return 0;
}
