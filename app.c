#include "floatbuffer.h"
#include <assert.h>
#include <errno.h>
#include <float.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constants */
static uint32_t const SAMPLE_RATE = 44100; // standard CD sample rate in Hz
static uint32_t const NYQUIST_SHANNON = SAMPLE_RATE / 2;
static char const OUTPUT_FILE[] = "out.raw";
static uint32_t const TRACK_LENGTH_SECONDS = SAMPLE_RATE * 2;

void pulse_wave(floatbuffer_t *buf, double freq, float amp, float duty_cycle);
void sawtooth_wave(floatbuffer_t *buf, double freq, float amp);

int main(void)
{
    double test_frequency = 55;
    float volume = 0.05f;
    floatbuffer_t buf = floatbuffer_new(TRACK_LENGTH_SECONDS);
    FILE *file = fopen(OUTPUT_FILE, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "Couldn't open file: %s\n", strerror(errno));
        return 1;
    }

    pulse_wave(&buf, test_frequency, volume, 0.2);
    // sawtooth_wave(&buf, test_frequency, volume);

    fwrite(buf.data, sizeof(float), TRACK_LENGTH_SECONDS, file);
    floatbuffer_del(buf);
    fclose(file);
    return 0;
}

void pulse_wave(floatbuffer_t *buf, double freq, float amp, float duty_cycle)
{
    assert(freq > 0 && freq < NYQUIST_SHANNON && amp > 0 && amp < 1 && duty_cycle > 0 && duty_cycle < 1);
    float const delta = freq / SAMPLE_RATE;
    float const MAX_AMP = 1.0;
    float const MIN_AMP = -1.0;
    float phase = 0.00;  // i.e. where in the period of the wave we are

    for (uint32_t i = 0; i < buf->capacity; i++)
    {
        if (phase < duty_cycle)
            floatbuffer_set(buf, MAX_AMP * amp);
        else
            floatbuffer_set(buf, MIN_AMP * amp);
        phase += delta;
        if (phase >= 1.0)
        {
            phase -= 1.0;
        }
    }
}

void sawtooth_wave(floatbuffer_t *buf, double freq, float amp)
{
    assert(freq > 0 && freq < NYQUIST_SHANNON && amp > 0 && amp < 1);
    float const delta = freq / SAMPLE_RATE;
    float phase = 0.00;
    float val = 0.00;

    for (uint32_t i = 0; i < buf->capacity; i++)
    {
        val = (phase - 0.5) * 2 * amp;
        floatbuffer_set(buf, val);
        phase += delta;
        if (phase >= 1.0)
        {
            phase -= 1.0;
        }
    }
}
