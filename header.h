#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include header file from the libcurl package
// Change path if installed in a different location
#include "../curl-7.74.0/include/curl/curl.h"

typedef struct BufferStruct {
        char *buffer;
        size_t size;
} BufferStruct ;

BufferStruct get_image(char *url);
char * base64_encode(char *url);

#endif /* HEADER_H */
