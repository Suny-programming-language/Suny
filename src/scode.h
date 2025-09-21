#ifndef SCODE_H
#define SCODE_H

#include "score.h"
#include "scompile.h"

struct Scompiler;

#define MAX_CODE_SIZE 1024

#define PUSH(code, c) Scode_add(code, c)

#define INSERT(code, c) Scode_push(code, c)

#define IS_BINARY_OPER(c) (c == BINARY_ADD || c == BINARY_SUB || c == BINARY_MUL || c == BINARY_DIV || c == BINARY_BIGGER_EQUAL || c == BINARY_BIGGER || c == BINARY_SMALLER_EQUAL || c == BINARY_SMALLER || c == BINARY_EQUAL || c == BINARY_NOT_EQUAL)

struct Scode {
    unsigned char code[MAX_CODE_SIZE];
    int size;
    int capacity;

    int line[MAX_CODE_SIZE];
    int size_line;
    int capacity_line;
};

struct Scode *
Scode_get_code_from(char* file, struct Scompiler *compiler);

struct Scode *
Scode_insert_to_top(struct Scode *code, struct Scode *insert);

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