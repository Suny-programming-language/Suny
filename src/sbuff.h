#ifndef SBUFF_H
#define SBUFF_H

#include "suny.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SZIO {
    char *file;
    char *buffer;
    int size;
};

struct SZIO*
Sbuff_new(void);

int
Sbuff_free(struct SZIO *zio);

struct SZIO*
Sbuff_read_file
(char* file);

#endif // SBUFF_H