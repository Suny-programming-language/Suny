#ifndef SBUFF_H
#define SBUFF_H

#include "score.h"

struct SZIO {
    char *file;
    char *buffer;
    int size;

    char** folders;
    int nf;
    int maxf;
    
};

struct SZIO*
Sbuff_new(void);

struct SZIO*
Sbuff_find_file_in(char* filename, char* path);

struct SZIO*
Sbuff_read_folder_name(char* path);

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