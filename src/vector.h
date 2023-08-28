#pragma once
#include <assert.h>
#include "utils.h"

typedef struct {
    void** data;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector* vec, size_t initial_capacity);
void vector_push_back(Vector* vec, void* value);
void* vector_at(const Vector* vec, size_t index);
void vector_free(Vector* vec);