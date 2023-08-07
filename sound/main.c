#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "audio.h"

#define DURATION 4
#define N (SAMPLE_RATE * DURATION)

#define C4 261.63f

int main(void)
{
	int16_t sound[N];

	for (int i = 0; i < N; ++i) {
		float t = (float){ i } / (float){ SAMPLE_RATE }; // in seconds

		float volume = sinf(2.0f * 3.1415f * 8.0f * t) + 1.0f / 2.0f;
		float amp = (float){ INT16_MAX } / 8.0f * volume; // oscilating volume

		if (i < N / 2) { // play sequentially
			enum wave type;

			if (i < N / 8)
				type = WAVE_SINE;
			else if (i < 2 * N / 8)
				type = WAVE_SQUARE;
			else if (i < 3 * N / 8)
				type = WAVE_SAW;
			else
				type = WAVE_TRIANGLE;

			sound[i] = wave_sample(C4, t, amp, type);
		} else { // play simultaneously
			sound[i] = 0.0f;

			if (i >= N / 2)
				sound[i] += wave_sample(C4, t, amp, WAVE_SINE);
			if (i > N / 2 + N / 8)
				sound[i] += wave_sample(C4, t, amp, WAVE_SQUARE);
			if (i > N / 2 + 2 * N / 8)
				sound[i] += wave_sample(C4, t, amp, WAVE_SAW);
			if (i > N / 2 + 3 * N / 8)
				sound[i] += wave_sample(C4, t + 0.1f, amp, WAVE_TRIANGLE);

			float n_waves = 1.0f + floorf((i - N / 2) / (N / 8));

			sound[i] /= n_waves; // avoid volume increase
		}
	}

	write_wav(sound, N, stdout);

	return 0;
}
