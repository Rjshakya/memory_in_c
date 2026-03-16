#include "union.h"
#include <stdio.h>

void format_object(snek_object_t obj, char *buffer)
{

  switch (obj.kind)
  {

  case INTEGER:
    sprintf(buffer, "int : %d\n", obj.data.v_int);
    break;
  case STRING:
    sprintf(buffer, "string : %s\n", obj.data.v_string);
    break;
  };
}

snek_object_t new_integer(int i)
{
  return (snek_object_t){
      .kind = INTEGER,
      .data = {.v_int = i},
  };
}

snek_object_t new_string(char *str)
{
  // NOTE: We will learn how to copy this data later.
  return (snek_object_t){
      .kind = STRING,
      .data = {.v_string = str},
  };
}

int main()
{

  char buffer[100];
  snek_object_t x = new_integer(8);
  snek_object_t y = new_string("i am string");

  format_object(y, buffer);
  printf("formated buffer %s\n", buffer);
};