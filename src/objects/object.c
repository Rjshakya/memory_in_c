#include "stdlib.h"
#include <stdio.h>
#include "object.h"
#include "string.h"
#include "stdbool.h"

// forward declaration for free
void refcount_free(snek_object_t *obj);

void refcount_inc(snek_object_t *obj)
{

    if (obj == NULL)
    {
        return;
    }

    obj->ref_count++;
}

void refcount_dec(snek_object_t *obj)
{
    if (obj == NULL)
    {
        return;
    }

    obj->ref_count--;

    if (obj->ref_count == 0)
    {
        refcount_free(obj);
    }
}

void refcount_free(snek_object_t *obj)
{

    if (obj->kind == INTEGER || obj->kind == FLOAT)
    {
        free(obj);
    }

    if (obj->kind == STRING)
    {
        free(obj->data.v_stirng);
        free(obj);
    }

    if (obj->kind == VECTOR3)
    {
        refcount_dec(obj->data.v_vector3.x);
        refcount_dec(obj->data.v_vector3.y);
        refcount_dec(obj->data.v_vector3.z);
    }

    if (obj->kind == ARRAY)
    {
        size_t size = obj->data.v_array.size;
        snek_object_t **elements = obj->data.v_array.elements;

        for (size_t i = 0; i < size; i++)
        {
            refcount_dec(elements[i]);
        }

        refcount_dec(*elements);
    }
}

// create new snek_object with refcount
snek_object_t *_new_snek_object()
{

    snek_object_t *obj = calloc(1, sizeof(snek_object_t));

    if (obj == NULL)
    {
        return NULL;
    }

    obj->ref_count = 1;
    return obj;
}

snek_object_t *new_snek_integer(int value)
{

    snek_object_t *obj = _new_snek_object();

    if (obj == NULL)
    {
        return NULL;
    }

    obj->kind = INTEGER;
    obj->data.v_int = value;

    return obj;
}

snek_object_t *new_snek_float(float value)
{

    snek_object_t *obj = _new_snek_object();
    if (obj == NULL)
    {
        return NULL;
    }
    obj->kind = FLOAT;
    obj->data.v_float = value;

    return obj;
}

snek_object_t *new_snek_string(char *value)
{

    snek_object_t *obj = _new_snek_object();

    if (obj == NULL)
    {
        return NULL;
    }

    size_t len = strlen(value);
    char *str_mem = malloc(len + 1);

    if (str_mem == NULL)
    {
        return NULL;
    }

    char *str = strncpy(str_mem, value, len + 1);

    obj->data.v_stirng = str;
    obj->kind = STRING;
    return obj;
}

snek_object_t *new_snek_vector3(
    snek_object_t *x,
    snek_object_t *y,
    snek_object_t *z)
{
    if (x == NULL || y == NULL || z == NULL)
    {
        return NULL;
    }

    snek_object_t *obj = _new_snek_object();

    if (obj == NULL)
    {
        return NULL;
    }

    obj->kind = VECTOR3;

    snek_vector_t vector = {
        .x = x,
        .y = y,
        .z = z};

    vector.x->ref_count++;
    vector.y->ref_count++;
    vector.z->ref_count++;

    obj->data.v_vector3 = vector;
    return obj;
}

snek_object_t *new_snek_array(size_t size)
{

    snek_object_t *obj = _new_snek_object();

    if (obj == NULL)
    {
        return NULL;
    }

    snek_object_t **elements = calloc(size, sizeof(snek_object_t *));

    if (elements == NULL)
    {
        free(obj);
        return NULL;
    }

    snek_array_t snek_arr = {
        .size = size,
        .elements = elements,
    };

    obj->kind = ARRAY;
    obj->data.v_array = snek_arr;

    return obj;
}

// set elements in snek_array
bool snek_array_set(
    snek_object_t *snek_obj,
    size_t index,
    snek_object_t *value)
{

    if (snek_obj == NULL || value == NULL)
    {
        return false;
    }

    if (snek_obj->kind != ARRAY)
    {
        return false;
    }

    if (index >= snek_obj->data.v_array.size)
    {
        return false;
    }

    size_t arr_size = snek_obj->data.v_array.size;
    snek_object_t **elements = snek_obj->data.v_array.elements;

    if (elements[index])
    {
        refcount_dec(elements[index]);
    }

    /*

        it is just a
        syntactic sugar of

        elements just a pointer,
        pointing to element
        (which is itself a pointer, pointing to snek_object/null)

        *(elements + index) (POINTER ARITHMETIC);

        it is saying ,
        pointer elements , go to
        plus index ,

        and deference that mem block.


    */
    elements[index] = value;
    refcount_inc(elements[index]);

    return true;
}

// get elements from snek_array
snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index)
{
    if (snek_obj == NULL || snek_obj->kind != ARRAY)
    {
        return NULL;
    }

    if (index >= snek_obj->data.v_array.size)
    {
        return NULL;
    }

    snek_object_t **elements = snek_obj->data.v_array.elements;
    size_t size = snek_obj->data.v_array.size;

    return elements[index];
}

int main()
{

    snek_object_t *s_int = new_snek_integer(40);
    snek_object_t *s_float = new_snek_float(40.5);
    snek_object_t *s_str = new_snek_string("i am a string object");
    snek_object_t *s_vector = new_snek_vector3(s_int, s_float, s_str);
    snek_object_t *s_arr = new_snek_array(10);

    bool is_set = snek_array_set(s_arr, 0, s_int);
    snek_object_t *get = snek_array_get(s_arr, 0);

    printf("s_int data is %d , and s_int kind is %d\n", s_int->data.v_int, s_int->kind);
    printf("s_float data is %f , and s_float kind is %d\n", s_float->data.v_float, s_float->kind);
    printf("s_str data is %s , and s_str kind is %d\n", s_str->data.v_stirng, s_str->kind);
    printf("s_vector_x data is %d , and s_vector kind is %d\n", s_vector->data.v_vector3.x->data.v_int, s_vector->kind);
    printf("s_vector_y data is %f , and s_vector kind is %d\n", s_vector->data.v_vector3.y->data.v_float, s_vector->kind);
    printf("s_vector_z data is %s , and s_vector kind is %d\n", s_vector->data.v_vector3.z->data.v_stirng, s_vector->kind);
    printf("snek_arr is of size %d\n", s_arr->data.v_array.size);

    printf("value at idx 0 in our array is %d\n", get->data.v_int);
    printf("kind at idx 0 in our array is %d\n", get->kind);

    return 0;
}