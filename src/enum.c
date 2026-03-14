#include <stdio.h>
#include "enum.h"

void http_to_str(http_errors_t errors)
{

    switch (errors)
    {
    case 0:
        printf("400 Bad Request\n");
        break;
    case 1:
        printf("401 Unauthorized\n");
        break;
    case 2:
        printf("404 Not Found\n");
        break;
    case 3:
        printf("418 I AM A TEAPOT!\n");
        break;
    case 4:
        printf("500 Internal Server Error\n");
        break;
    default:
        printf("Unknown HTTP status code\n");
        break;
    }
}

int main()
{

    color_t my_col = BLUE;
    printf("my color is %d\n", my_col);
    http_errors_t error = HTTP_BAD_REQUEST;
    http_to_str(error);

    printf("size of httperrors is %zu\n", sizeof(http_errors_t));
}