#define _DEFAULT_SOURCE // M_PI

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "audio.h"

int16_t sine_sample(float hertz, float t, float volume)
{
	float b = 2.0f * M_PI * hertz;

	return sinf(b * t) * volume;
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
	fwrite(&(uint32_t){ SAMPLE_RATE * 16 / 8 }, 4, 1, stream); // byte rate
	fwrite(&(uint16_t){ 16 / 8 }, 2, 1, stream); // block align
	fwrite(&(uint16_t){ 16 }, 2, 1, stream); // bit size

	fprintf(stream, "data");
	fwrite(&(uint32_t){ n * 2 }, 4, 1, stream); // data size
	fwrite(data, n * 2, 1, stream);
}
