#define SAMPLE_RATE 44100

/*
enum wave {
	WAVE_SINE,
	WAVE_SQUARE,
	WAVE_TRIANGLE,
	WAVE_SAW
};

int16_t wave_sample(float hertz, float t, float volume, enum wave type);
*/

int16_t sine_sample(float hertz, float t, float volume);

void write_wav(int16_t *data, int n, FILE *stream);
