#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "audio.h"

#define DURATION 10
#define N (SAMPLE_RATE * DURATION)

#define C4 261.63f

int main(void)
{
	int16_t sound[N];

	float wave_time = (float){ N } / 10.0f; // duration for each wave

	for (int i = 0; i < N; ++i) {
		float t = (float){ i } / (float){ SAMPLE_RATE }; // in seconds

		float volume = (sinf(2.0f * M_PI * t - M_PI / 2.0f) + 1.0f) / 2.0f;
		float amp = (float){ INT16_MAX } / 8.0f * volume; // oscilating volume

		if (i < N / 2) { // play sequentially
			enum wave type;

			if (i < wave_time)
				type = WAVE_SINE;
			else if (i < 2 * wave_time)
				type = WAVE_SQUARE;
			else if (i < 3 * wave_time)
				type = WAVE_SAW;
			else if (i < 4 * wave_time)
				type = WAVE_TRIANGLE;
			else
				type = WAVE_NOISE;

			sound[i] = wave_sample(C4, t, amp, type);
		} else { // play simultaneously
			sound[i] = 0.0f;

			if (i >= N / 2)
				sound[i] += wave_sample(C4, t, amp, WAVE_SINE);
			if (i > N / 2 + wave_time)
				sound[i] += wave_sample(C4, t, amp, WAVE_SQUARE);
			if (i > N / 2 + 2 * wave_time)
				sound[i] += wave_sample(C4, t, amp, WAVE_SAW);
			if (i > N / 2 + 3 * wave_time)
				sound[i] += wave_sample(C4, t, amp, WAVE_TRIANGLE);
			if (i > N / 2 + 4 * wave_time)
				sound[i] += wave_sample(C4, t, amp, WAVE_NOISE);
		}
	}

	write_wav(sound, N, stdout);

	return 0;
}
