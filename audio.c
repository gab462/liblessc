#define _DEFAULT_SOURCE // M_PI

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "audio.h"

int16_t wave_sample(float hertz, float t, float amplitude, enum wave type)
{
	float y = 0.0f;

	switch (type) {
	case WAVE_SINE:
		y = sinf(2.0f * M_PI * hertz * t);
		break;
	case WAVE_SQUARE:
		y = 1.0f - 2.0f * (sinf(2.0f * M_PI * hertz * t) > 0.0f);
		break;
	case WAVE_TRIANGLE:
		y = 2.0f * fabsf(hertz * t - floorf(hertz * t + 0.5f));
		break;
	case WAVE_SAW:
		y = 2.0f * (hertz * t - floorf(0.5f + hertz * t));
		break;
	default:
		break;
	}

	return y * amplitude;
}

void write_wav(int16_t *data, int n, FILE *stream)
{
	fprintf(stream, "RIFF");
	fwrite(&(uint32_t){ 36 + n * 2 }, 4, 1, stream); // total size
	fprintf(stream, "WAVE");

	fprintf(stream, "fmt ");
	fwrite(&(uint32_t){ 16 }, 4, 1, stream); // subchunk size
	fwrite(&(uint16_t){ 1 }, 2, 1, stream); // audio format
	fwrite(&(uint16_t){ 1 }, 2, 1, stream); // channels
	fwrite(&(uint32_t){ SAMPLE_RATE }, 4, 1, stream); // sample rate
	fwrite(&(uint32_t){ SAMPLE_RATE * 2 }, 4, 1, stream); // byte rate
	fwrite(&(uint16_t){ 2 }, 2, 1, stream); // block align
	fwrite(&(uint16_t){ 16 }, 2, 1, stream); // bit size

	fprintf(stream, "data");
	fwrite(&(uint32_t){ n * 2 }, 4, 1, stream); // data size
	fwrite(data, n * 2, 1, stream);
}
