#ifndef SBUFF_H
#define SBUFF_H

#include "score.h"

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
Sbuff_free
(struct SZIO *zio);

struct SZIO*
Sbuff_read_file
(char* file);

struct SZIO* 
Sbuff_write_bytecode_file
(unsigned char* content, size_t size, const char* filename);

#endif // SBUFF_H