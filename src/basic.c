#include "coord.h"
#include <stdio.h>

void coord_update_x(coord_t coord, int x) {
  coord.x = x;
  return;
}

coord_t coord_update_and_return_x(coord_t coord, int x) {
  coord.x = x;
  return coord;
}

int main() { 
    
    coord_t c = {.x = 40, .y = 50, .z = 60};
    coord_update_x(c, 60);
    printf("%d\n" , c.x);
    coord_t updated = coord_update_and_return_x(c, 80);
    printf("%d\n" , updated.x);

}
