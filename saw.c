#include <stdio.h>

int saw()
{
    float freq = 440;
    float sample_rate = 44100; // standard CD sample rate in Hz
    float delta = freq / sample_rate;
    float position = 0.00;
    float buffer[88200];
    FILE *file = fopen("out.raw", "wb");
    if (file == NULL)
        return 1;

    for (int i = 0; i < 88200; i++) {
        buffer[i] = 2.0 * (position - 0.5);
        position += delta;
        if (position >= 1.0) {
	    position -= 1.0;
	}
    }

    fwrite(buffer, sizeof(float), 88200, file);

    fclose(file);
    return 0;
}
