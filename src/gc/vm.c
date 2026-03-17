#include <stdlib.h>
#include <stdio.h>
#include "vm.h"
#include "stack.h"
#include "object.h"
#include "snekobject.h"

void vm_collect_garbage(vm_t *vm) {
  mark(vm);
  trace(vm);
  sweep(vm);

}

void sweep(vm_t *vm) {
  
    for (size_t i = 0; i < vm->objects->count; i++)
    {
        snek_object_t *obj = vm->objects->data[i];

        if(obj->is_marked){
            obj->is_marked = false;
        }else{
            snek_object_free(obj);
            vm->objects->data[i] = NULL;

        }
    
    }

        stack_remove_nulls(vm->objects);
    
}

void trace(vm_t *vm)
{
    stack_t *gray_objects = stack_new(8);
    if (gray_objects == NULL)
    {
        return;
    }

    for (size_t i = 0; i < vm->objects->count; i++)
    {
        snek_object_t *obj = vm->objects->data[i];

        if (obj && obj->is_marked)
        {
            stack_push(gray_objects, (void *)obj);
        }
    }

    while (gray_objects->count)
    {

        snek_object_t *obj = stack_pop(gray_objects);
        trace_blacken_object(gray_objects, obj);
    }

    stack_free(gray_objects);
}

void trace_blacken_object(stack_t *gray_objects, snek_object_t *obj)
{

    if (gray_objects == NULL || obj == NULL)
    {
        return;
    }

    if (obj->kind == VECTOR3)
    {
        trace_mark_object(gray_objects, obj->data.v_vector3.x);
        trace_mark_object(gray_objects, obj->data.v_vector3.y);
        trace_mark_object(gray_objects, obj->data.v_vector3.z);
    }
    else if (obj->kind == ARRAY)
    {

        size_t arr_size = obj->data.v_array.size;
        for (size_t i = 0; i < arr_size; i++)
        {
            snek_object_t *elem = obj->data.v_array.elements[i];
            trace_mark_object(gray_objects, elem);
        }
    }
}

void trace_mark_object(stack_t *gray_objects, snek_object_t *obj)
{

    if (obj == NULL)
    {
        return;
    }

    if (obj->is_marked)
    {
        return;
    }

    obj->is_marked = true;
    stack_push(gray_objects, (void *)obj);
}

void mark(vm_t *vm)
{
    if (vm == NULL || vm->frames == NULL)
    {
        return;
    }

    for (size_t i = 0; i < vm->frames->count; i++)
    {

        frame_t *frame = vm->frames->data[i];
        for (size_t i = 0; i < frame->references->count; i++)
        {
            stack_t *stack = frame->references->data[i];
            snek_object_t *obj = stack->data;
            obj->is_marked = true;
        }
    }
}

void frame_reference_object(frame_t *frame, snek_object_t *obj)
{

    if (frame == NULL || obj == NULL)
    {
        return;
    }

    stack_push(frame->references, (void *)obj);
}

void vm_free(vm_t *vm)
{

    for (size_t i = 0; i < vm->frames->count; i++)
    {

        frame_free(vm->frames->data[i]);
    }

    stack_free(vm->frames);

    for (size_t i = 0; i < vm->objects->count; i++)
    {
        snek_object_free(vm->objects->data[i]);
    }

    stack_free(vm->objects);

    free(vm);
}

void vm_track_object(vm_t *vm, snek_object_t *obj)
{
    if (vm == NULL || obj == NULL)
    {
        return NULL;
    }
    stack_push(vm->objects, (void *)obj);
}

void vm_frame_push(vm_t *vm, frame_t *frame)
{

    stack_push(vm->frames, frame);
}

frame_t *vm_new_frame(vm_t *vm)
{
    frame_t *frame = malloc(sizeof(frame_t));

    if (frame == NULL)
    {
        return NULL;
    }

    frame->references = stack_new(8);
    if (frame->references == NULL)
    {
        free(frame);
        return NULL;
    }
    vm_frame_push(vm, frame);

    return frame;
}

void frame_free(frame_t *frame)
{
    if (frame == NULL)
    {
        return NULL;
    }
    stack_free(frame->references);
    free(frame);
}

vm_t *vm_new()
{

    vm_t *vm = malloc(sizeof(vm_t));

    if (vm == NULL)
    {
        return NULL;
    }

    vm->frames = stack_new(8);

    if (vm->frames == NULL)
    {
        free(vm);
        return NULL;
    }
    vm->objects = stack_new(8);

    if (vm->objects == NULL)
    {
        free(vm);
        return NULL;
    }

    return vm;
}

void vm_free(vm_t *vm)
{
    if (vm == NULL)
    {
        return;
    }

    for (int i = 0; i < vm->frames->count; i++)
    {
        frame_free(vm->frames->data[i]);
    }

    stack_free(vm->frames);
    stack_free(vm->objects);

    free(vm);
}

int main()
{

    return 0;
}