#include "vector.h"
#include "ast.h"

void vector_init(Vector* vec, size_t initial_capacity)
{
    vec->data = NULL;
    // vec->data = malloc(initial_capacity * sizeof(ast_node_t*));
    // if (vec->data == nullptr) {
    //     fatal_error("Memory reallocation failed.\n");
    //     exit(1);
    // }
    vec->size = 0;
    vec->capacity = initial_capacity;
}

void vector_push_back(Vector* vec, void* value)
{
    // printf("vec size: %i\n", vec->size);
    vec->capacity *= 2;
    vec->data = realloc(vec->data, ++vec->size * sizeof(ast_node_t*));
    if (vec->data == nullptr) {
        fatal_error("Memory reallocation failed.\n");
        exit(1);
    }
    
    vec->data[vec->size - 1] = value;
}

void* vector_at(const Vector* vec, size_t index)
{
    assert(index < vec->size);
    return vec->data[index];
}

void vector_free(Vector* vec)
{
    free(vec->data);
    vec->data = nullptr;
    vec->size = 0;
    vec->capacity = 0;
}