#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "floatbuffer.h"

floatbuffer_t floatbuffer_new(uint32_t capacity)
{
    floatbuffer_t buf = {.capacity = 0, .length = 0, .data = NULL};
    float *new_data = malloc(capacity * sizeof(float));
    if (new_data == NULL)
    {
        fprintf(stderr, "Failed to allocate floatbuffer_t: %s\n", strerror(errno));
        return buf;
    }
    memset(new_data, 0.00f, capacity);
    buf.data = new_data;
    buf.capacity = capacity;
    return buf;
}

void floatbuffer_del(floatbuffer_t buf)
{
    // Check if already free
    if (buf.data == NULL)
    {
        fprintf(stderr, "floatbuffer_t.data already free: %s\n", strerror(errno));
        return;
    }
    else
    {
        free(buf.data);
    }
}

void floatbuffer_set(floatbuffer_t *buf, float value)
{
    // if buffer full, perror and return without setting value
    if (buf->length == buf->capacity)
    {
        fprintf(stderr, "floatbuffer_t full: %s\n", strerror(errno));
        printf("check failed!\n");
        return;
    }
    else
    {
        // check to make sure these indices are correct
        buf->data[buf->length] = value;
        buf->length++;
        return;
    }
}

float floatbuffer_get(floatbuffer_t buf, size_t index)
{
    // Runtime bounds checking
    if (index < buf.length)
    {
        return buf.data[index];
    }
    // error case put debugger breakpoint after this line
    return 0;
}
