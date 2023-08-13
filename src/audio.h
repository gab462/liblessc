// audio soundwave synthesis

#define SAMPLE_RATE 44100

enum wave {
	WAVE_SINE,
	WAVE_SQUARE,
	WAVE_TRIANGLE,
	WAVE_SAW,
	WAVE_NOISE
};

int16_t wave_sample(float hertz, float t, float amplitude, enum wave type);

void write_wav(int16_t *data, int n, FILE *stream);
