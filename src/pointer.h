#pragma once
#include <string.h>

typedef struct Coord
{
    int x;
    int y;
    int z;
} coord_t;


typedef struct CodeFile {
  int lines;
  int filetype;
} codefile_t;


typedef struct {
  size_t length;
  char buffer[64];
} TextBuffer;
