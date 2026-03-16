#include <stdio.h>
#include <stdlib.h>

char *get_full_greeting(char *greeting, char *name, int size)
{

  char *full_greeting = malloc(size);
  if (full_greeting == NULL)
  {
    return NULL;
  };

  snprintf(full_greeting, size, "%s %s", greeting, name);

  return full_greeting;
}

int *allocate_scalar_array(int size, int multiplier)
{

  int *arr = malloc(size * sizeof(int));

  if (arr == NULL)
  {
    return NULL;
  };

  for (int i = 0; i < size; i++)
  {
    arr[i] = i * multiplier;
  }

  return arr;
}

int free_alloc()
{

  const int num_lists = 500;
  for (int i = 0; i < num_lists; i++)
  {
    int *lst = allocate_scalar_array(50000, 2);
    if (lst == NULL)
    {
      printf("Failed to allocate list\n");
      return 1;
    }
    else
    {
      printf("Allocated list %d\n", i);
    }

    free(lst);
  }

  return 0;
}

int main()
{

  // char *greeting = "greet";
  // char *name = "raj";

  // char *greeted = get_full_greeting(greeting, name, 100);

  // printf("greeted done %s\n", greeted);

  // int size = 5;
  // int multiplier = 2;

  // int *alloc_arr = allocate_scalar_array(size, multiplier);

  // printf("allocated arr is %d\n", alloc_arr[5]);

  free_alloc();

  return 0;
}