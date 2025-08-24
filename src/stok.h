#ifndef STOK_H
#define STOK_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_IDENTIFIER_SIZE 1024
#define MAX_NUMBER_LEN 1024

#define NULL_TOKEN Stok_init(NULL_TOK, 0, NULL)

#define EOF_TOKEN Stok_init(EOF_TOK, 0, NULL)

#define TOKEN(t, v, l) Stok_init(t, v, l)

#define IS_TOK_EXPR_START(t) ( \
    (t)->type == IDENTIFIER || \
    (t)->type == STRING     || \
    (t)->type == ADD        || \
    (t)->type == SUB        || \
    (t)->type == MUL        || \
    (t)->type == DIV        || \
    (t)->type == LPAREN     || \
    (t)->type == RPAREN     || \
    (t)->type == LBRACKET   || \
    (t)->type == RBRACKET   )

enum Stok_t {
    DIV,
    MUL,
    ADD,
    SUB,
    NUMBER,
    STRING,
    IDENTIFIER,
    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,
    PRINT_T,
    ASSIGN,
    EQUALS,
    NULL_TOK,
    LET,
    IF,
    WHILE,
    DO,
    FOR,
    RETURN,
    EOF_TOK,
    UNKNOWN_T,
};

struct Stok {
    enum Stok_t type;
    float value;
    char *lexeme;
};

char* 
Stok_t_print
(enum Stok_t type);

struct Stok *
Stok_new(void);

struct Stok *
Stok_init
(enum Stok_t type, float value, char *lexeme);

int
Stok_free
(struct Stok *token);

enum Stok_t
get_1_char
(char c);

#endif // STOK_H