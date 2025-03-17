#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <stdint.h>
#include "./floatbuffer.h"

int main(void)
{
    float freq = 110;
    float sample_rate = 44100; // standard CD sample rate in Hz
    float delta = freq / sample_rate;
    float position = 0.00;
    floatbuffer_t buf = floatbuffer_new(88200);
    FILE *file = fopen("out.raw", "wb");
    if (file == NULL)
    {
        fprintf(stderr, "Couldn't open out.raw: %s\n", strerror(errno));
        return 1;
    }

    for (uint32_t i = 0; i < buf.capacity; i++)
    {
        if (position < 0.5)
            floatbuffer_set(&buf, 1.0);
        else
            floatbuffer_set(&buf, -1.0);
        position += delta;
        if (position >= 1.0)
        {
            position -= 1.0;
        }
    }

    fwrite(buf.data, sizeof(float), 88200, file);
    floatbuffer_del(buf);
    fclose(file);
    return 0;
}
