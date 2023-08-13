#include <stdint.h>
#include <math.h>
#include <stdio.h> // FILE
#include <stdlib.h> // rand

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
	case WAVE_NOISE:
		y = 2.0f * (float){ rand() } / (float){ RAND_MAX } - 1.0f;
		break;
	default:
		break;
	}

	return y * amplitude;
}

void write_u32(uint32_t data, FILE *stream)
{
	fwrite(&data, sizeof(data), 1, stream);
}

void write_u16(uint16_t data, FILE *stream)
{
	fwrite(&data, sizeof(data), 1, stream);
}

void write_wav(int16_t *data, int n, FILE *stream)
{
	fprintf(stream, "RIFF");
	write_u32(36 + n * 2, stream); // total size
	fprintf(stream, "WAVE");

	fprintf(stream, "fmt ");
	write_u32(16, stream); // subchunk size
	write_u16(1, stream); // audio format
	write_u16(1, stream); // channels
	write_u32(SAMPLE_RATE, stream); // sample rate
	write_u32(SAMPLE_RATE * 2, stream); // byte rate
	write_u16(2, stream); // block align
	write_u16(16, stream); // bit size

	fprintf(stream, "data");
	write_u32(n * 2, stream); // data size
	fwrite(data, n * 2, 1, stream);
}
