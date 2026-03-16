/**
 *  Advance Pointer
 */

#include "stdlib.h"
#include <stdio.h>

void *allocate_int(int **pointer_pointer, int value)
{
    int *val_pointer = malloc(sizeof(int));

    if(val_pointer == NULL){
        return NULL;
    };
    
    *pointer_pointer = val_pointer;
    **pointer_pointer = value;

}

int main()
{
    int *pointer = NULL;
    allocate_int(&pointer , 10);

    
    printf("allocated pointer is %d\n" , *pointer);
    return 0;
}