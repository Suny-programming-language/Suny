#ifndef STOK_H
#define STOK_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ssyntax.h"

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
    DIV, MUL, ADD, SUB,

    NUMBER, STRING, IDENTIFIER,

    LPAREN, RPAREN,
    LBRACKET, RBRACKET,

    ADD_ASSIGN, SUB_ASSIGN, MUL_ASSIGN, DIV_ASSIGN,

    ASSIGN,
    EQUALS,
    NOT_EQUALS,
    IS,
    BIGGER, BIGGER_EQUALS,
    SMALLER, SMALLER_EQUALS,

    AND,
    OR,
    NOT,

    INCLUDE,
    IMPORT,

    ANONYMOUS,

    TRUE_T,
    FALSE_T,

    CLASS,
    EXTENDS,

    LET,
    IF, ELSE, THEN, ELIF,
    WHILE, DO, END, BREAK, CONTINUE,
    FOR, IN_T,
    FUNCTION, RETURN,

    NULL_TOK,
    PRINT_T,

    COMMA,
    DOT,
    COLON,
    SEMICOLON,

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

enum Stok_t 
Stok_get_identifier
(char *lexeme);

struct Stok *
Stok_init
(enum Stok_t type, float value, char *lexeme);

int
Stok_free
(struct Stok *token);

enum Stok_t
get_1_char
(char c);

enum Stok_t 
get_2_char
(char c1, char c2);

int
is_2_char
(char c1, char c2);

#endif // STOK_H