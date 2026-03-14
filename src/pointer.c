
#include "pointer.h"
#include <stdio.h>
#include <string.h>

void coord_update_x(coord_t coord, int x)
{
    coord.x = x;
    return;
}

coord_t coord_update_and_return_x(coord_t coord, int x)
{
    coord.x = x;
    return coord;
}

codefile_t change_filetype(codefile_t *f, int new_filetype)
{
    codefile_t new_f = *f;
    new_f.filetype = new_filetype;
    return new_f;
}

void update_file(int filedata[200], int new_filetype, int new_num_lines)
{
    filedata[1] = new_num_lines;
    filedata[2] = new_filetype;
    filedata[199] = 0;
}

// void core_utils_func(int core_utilization[])
// {
//     printf("sizeof core_utilization in core_utils_func: %d\n", sizeof(core_utilization));
// }

void concat_strings(char *str1, const char *str2)
{

    while (*str1 != '\0')
    {
        str1++;
    };

    while (*str2 != '\0')
    {
        *str1 = *str2;
        str1++;
        str2++;
    }

    *str1 = '\0';
}

// void array_decay()
// {
//     int core_utilization[] = {43, 67, 89, 92, 71, 43, 56, 12};
//     int len = sizeof(core_utilization) / sizeof(core_utilization[0]);
//     printf("sizeof core_utilization in main: %zu\n", sizeof(core_utilization));
//     printf("len of core_utilization: %d\n", len);
//     core_utils_func(core_utilization);
// }

int smart_append(TextBuffer *dest, const char *src)
{

    if (!dest || !*src)
    {
        return NULL;
    };

    const int bufferSize = 64;
    int srcLen = strlen(src);
    int remaining = (bufferSize - 1) - dest->length;

    if (remaining <= 0) {
        return 1; // Full append not possible (buffer full)
    }


    if (srcLen > remaining)
    {
        strncat(dest->buffer, src, remaining);
        dest->length = remaining + 1;
        return 1;
    }
    else
    {
        strncat(dest->buffer, src, srcLen);
        dest->length = srcLen + 1;
        return 0;
    };

    return 0;
}

int main()
{

    char c[100] = "hello";
    const char *c2 = "world";
    concat_strings(c, c2);

    printf("c is %s\n", c);
}
