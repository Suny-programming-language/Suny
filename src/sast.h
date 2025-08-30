#ifndef SAST_H
#define SAST_H

#include <stdlib.h>
#include <string.h>

#include "stok.h"
#include "slexer.h"

#define MAX_STATEMENT_SIZE 1024

#define AST(t, v, l) Sast_init(t, v, l)

#define is_expr(ast) ((ast)->type == AST_EXPRESSION                         \
                        || (ast)->type == AST_BINARY_EXPRESSION             \
                        || (ast)->type == AST_IDENTIFIER                    \
                        || (ast)->type == AST_FUNCTION_CALL_EXPRESSION       \
                        || (ast)->type == AST_AND_EXPRESSION                \
                        || (ast)->type == AST_OR_EXPRESSION                 \
                        || (ast)->type == AST_NOT_EXPRESSION                \
                        || (ast)->type == AST_COMPARE_EXPRESSION            \
                        || (ast)->type == AST_LIST                          \
                        || (ast)->type == AST_EXTRACT                       \
                        || (ast)->type == AST_LITERAL                       \
                        || (ast)->type == AST_STRING_EXPRESSION)

enum Sast_t {
    AST_PROGRAM,
    AST_BLOCK,
    AST_STATEMENT,
    AST_EXPRESSION,
    AST_PRINT,
    AST_BREAK,
    AST_CONTINUE,
    AST_ASSIGNMENT,
    AST_IF,
    AST_WHILE,
    AST_DO_LOOP,
    AST_COMPARE_EXPRESSION,
    AST_AND_EXPRESSION,
    AST_RETURN_STATEMENT,
    AST_OR_EXPRESSION,
    AST_STORE_INDEX,
    AST_NOT_EXPRESSION,
    AST_FUNCTION_CALL_EXPRESSION,
    AST_FUNCTION_STATEMENT,
    AST_FOR,
    AST_BINARY_EXPRESSION,
    AST_IDENTIFIER,
    AST_LITERAL,
    AST_STRING_EXPRESSION,    
    AST_LIST,
    AST_EXTRACT,
    AST_NULL,
};

struct Sast {
    enum Sast_t type;

    float value;
    char *lexeme;

    struct Sast *print_value;
    struct Sast *expr;

    struct Sast *left;
    struct Sast *right;
    enum Stok_t op;

    struct Sast *condition;
    struct Sast **if_body;
    struct Sast **else_body;
    
    int if_body_size;
    int else_body_size;

    struct Sast **params;
    struct Sast **body;
    int body_size;
    char **param_names;
    int is_having_params;

    int param_count;
    int args_count;

    struct Sast **block;
    int block_size;

    struct Sast *var_value;
    char *var_name;
    
    struct Sast **children;

    int child_count;
    int child_capacity;

    int block_count;
    int block_capacity;

    int ast_line;
    int ast_column;

    struct Sast *ret_val;

    struct Sast** list;

    int list_count;
    int list_capacity;

    struct Sast *extract_obj;
    struct Sast *extract_value;

    struct Slexer *lexer;
};

int Sast_set_line(struct Slexer *lexer, struct Sast *sast);

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

int 
Sast_add_block
(struct Sast *parent, struct Sast *child);

int
Sast_set_para
(struct Sast *func, char* param_names);

int
Sast_add_args
(struct Sast *func, struct Sast *param);

struct Sast* 
Sast_get_child
(struct Sast *sast, int index);

struct Sast*
Sast_add_element(struct Sast *list, struct Sast *element);

#endif