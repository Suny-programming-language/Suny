#ifndef SAST_H
#define SAST_H

#include <stdlib.h>
#include <string.h>

#include "stok.h"

#define AST(t, v, l) Sast_init(t, v, l)

enum Sast_t {
    AST_PROGRAM,
    AST_BLOCK,
    AST_STATEMENT,
    AST_EXPRESSION,
    AST_PRINT,
    AST_ASSIGNMENT,
    AST_IF,
    AST_WHILE,
    AST_DO_LOOP,
    AST_FOR,
    AST_BINARY_EXPRESSION,
    AST_IDENTIFIER,
    AST_LITERAL,
    AST_STRING_EXPRESSION,    
    AST_NULL,
};

struct Sast {
    enum Sast_t type;

    float value;
    char *lexeme;

    struct Sast *print_value;

    struct Sast *left;
    struct Sast *right;
    enum Stok_t op;

    struct Sast *var_value;
    char *var_name;
    
    struct Sast **children;

    int child_count;
    int child_capacity;
};

struct Sast* 
Sast_new(void);

struct Sast* 
Sast_init
(enum Sast_t type, float value, char *lexeme);

int 
Sast_free
(struct Sast *sast);

int 
Sast_add_child
(struct Sast *parent, struct Sast *child);

int 
Sast_print
(struct Sast *sast);

#endif