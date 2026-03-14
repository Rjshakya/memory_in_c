#pragma once

typedef enum Colors
{
    RED=55,
    GREEN=176,
    BLUE=38

} color_t;

typedef enum HttpErrors{

    HTTP_BAD_REQUEST,
    HTTP_UNAUTHORIZED,
    HTTP_NOT_FOUND,
    HTTP_TEAPOT,
    HTTP_INTERNAL_SERVER_ERROR,
}http_errors_t;