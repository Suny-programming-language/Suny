#ifndef SCODE_H
#define SCODE_H

#include "suny.h"

#define MAX_CODE_SIZE 1024

#define PUSH(code, c) Scode_add(code, c)

#define INSERT(code, c) Scode_push(code, c)

struct Scode {
    unsigned char code[MAX_CODE_SIZE];
    int size;
};

struct Scode *
Scode_new(void);

int 
Scode_free
(struct Scode *code);

int 
Scode_add
(struct Scode *code, unsigned char c);

int
Scode_push
(struct Scode *scode, struct Scode *code);

int
Scode_print
(struct Scode *code);

#endif // SCODE_H 