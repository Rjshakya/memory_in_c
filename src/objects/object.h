#include <stdio.h>
typedef struct SnekObject snek_object_t;

typedef struct SnekVector
{
    snek_object_t *x;
    snek_object_t *y;
    snek_object_t *z;

} snek_vector_t;

typedef struct SnekArray
{
    size_t size;
    snek_object_t **elements;
} snek_array_t;

typedef enum SnekObjectKind
{
    INTEGER,
    FLOAT,
    STRING,
    VECTOR3,
    ARRAY
} snek_object_kind_t;

typedef union SnekObjectData
{
    int v_int;
    float v_float;
    char *v_stirng;
    snek_vector_t v_vector3;
    snek_array_t v_array;
} snek_object_data_t;

typedef struct SnekObject
{
    snek_object_kind_t kind;
    snek_object_data_t data;
    int ref_count;
} snek_object_t;

snek_object_t *new_snek_integer(int value);
