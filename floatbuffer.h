#ifndef FLOATBUFFER_H
#define FLOATBUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <error.h>

typedef struct
{
    float *data;  // pointer to first element
    uint32_t length;   // number of elements in buf
    uint32_t capacity; // current capacity in bytes
} floatbuffer_t;

floatbuffer_t floatbuffer_new(uint32_t capacity);
void floatbuffer_del(floatbuffer_t buffer);
void floatbuffer_set(floatbuffer_t *buffer, float value);
float floatbuffer_get(floatbuffer_t buffer, size_t index);

#endif // FLOATBUFFER_H
