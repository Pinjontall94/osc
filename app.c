#include "./include/stdint_aliases.h"
#include <error.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    float *data;  // pointer to first element
    u32 length;   // number of elements in buf
    u32 capacity; // current capacity in bytes
} FloatBuffer;

float FloatBuffer_Get(FloatBuffer float_buffer, u32 index)
{
    // Runtime bounds checking
    if (index >= 0 && index < float_buffer.length)
    {
        return float_buffer.data[index];
    }
    // error case put debugger breakpoint after this line
    return 0;
}

void FloatBuffer_Set(FloatBuffer *float_buffer, float value)
{
    // if buffer full, perror and return without setting value
    if (float_buffer->capacity < 1)
    {
        perror("FloatBuffer full");
        return;
    }
    else
    {
        // check to make sure these indices are correct
        float_buffer->data[float_buffer->length] = value;
        float_buffer->length++;
        float_buffer->capacity--;
        return;
    }
}

FloatBuffer FloatBuffer_New(u32 capacity)
{
    FloatBuffer float_buffer = {.capacity = 0, .length = 0, .data = NULL};
    float *new_data = malloc(capacity * sizeof(float));
    if (new_data == NULL)
    {
        perror("Failed to allocate FloatBuffer");
        return float_buffer;
    }
    memset(new_data, 0.00f, capacity);
    float_buffer.data = new_data;
    float_buffer.capacity = capacity;
    return float_buffer;
}

void FloatBuffer_Del(FloatBuffer float_buffer)
{
    // Check if already free
    if (float_buffer.data == NULL)
    {
        perror("FloatBuffer.data already free");
        return;
    }
    else
    {
        free(float_buffer.data);
    }
}

int main()
{
    float freq = 440;
    float sample_rate = 44100; // standard CD sample rate in Hz
    float delta = freq / sample_rate;
    float position = 0.00;
    FloatBuffer buf = FloatBuffer_New(88200);
    FILE *file = fopen("out.raw", "wb");
    if (file == NULL)
    {
        perror("Couldn't open out.raw");
        return 1;
    }

    for (u32 i = 0; i < buf.capacity; i++)
    {
        if (position < 0.5)
            FloatBuffer_Set(&buf, 1.0);
        else
            FloatBuffer_Set(&buf, -1.0);
        position += delta;
        if (position >= 1.0)
        {
            position -= 1.0;
        }
    }

    fwrite(buf.data, sizeof(float), 88200, file);
    FloatBuffer_Del(buf);
    fclose(file);
    return 0;
}
