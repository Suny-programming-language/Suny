#ifndef SLEXER_H
#define SLEXER_H

#include "stok.h"
#include "sbuff.h"
#include "stool.h"
#include "serror.h"

#define newline(lexer) (lexer->line++, lexer->column = 0)

#define down(lexer) (lexer->index--, lexer->column--)

#define up(lexer) (lexer->index++, lexer->column++)

#define whitespace(lexer) (lexer->cur == ' ' || lexer->cur == '\t' || lexer->cur == '\n')

#define isdigit(lexer) (lexer->cur >= '0' && lexer->cur <= '9')

#define isalpha(lexer) (lexer->cur >= 'a' && lexer->cur <= 'z' || lexer->cur >= 'A' && lexer->cur <= 'Z')

#define isalnum(lexer) (isalpha(lexer) || isdigit(lexer))

#define is_potential_identifier_char(lexer) (isalpha(lexer) || lexer->cur == '_')

#define is_potential_digit_char(lexer) (isdigit(lexer) || lexer->cur == '.')

#define get_next_c(lexer) (lexer->cur = lexer->input[lexer->index++], lexer->column++)

#define current(lexer) (lexer->cur = lexer->input[lexer->index], lexer->next = lexer->input[lexer->index + 1], lexer->prev = lexer->input[lexer->index - 1])

#define is_keyword(c) ( \
    (c) == '!'  || (c) == '@'  || (c) == '#'  || (c) == '$'  || \
    (c) == '%'  || (c) == '^'  || (c) == '&'  || (c) == '*'  || \
    (c) == '('  || (c) == ')'  || (c) == '_'  || (c) == '+'  || \
    (c) == '/'  || (c) == '<'  || (c) == '>'  || (c) == ';'  || \
    (c) == '\'' || (c) == '{'  || (c) == '}'  || (c) == '['  || \
    (c) == ']'  || (c) == '\\' || (c) == '~'  || (c) == '='  || \
    (c) == '|'  || (c) == ':'  || (c) == '?'  || (c) == '-'     \
)

#define is_lexer_key(lexer) (is_keyword(lexer->cur))

struct Slexer {
    struct Stok *token;

    char *input;

    char cur;
    char next;
    char prev;

    int line;
    int column;

    int index;

    struct Stok *tok_stack[MAX_STACK_SIZE];
    int stack_size;
    int stack_index;

    struct SZIO *file;
};

struct Slexer *
Slexer_new(void);

struct Slexer *
Slexer_init
(char *input);

int 
Slexer_free
(struct Slexer *lexer);

char 
Slexer_get_next_c
(struct Slexer *lexer);

int 
Slexer_skip_whitespace
(struct Slexer *lexer);

int 
Slexer_skip_comment
(struct Slexer *lexer);

struct Stok *
Slexer_get_next_token
(struct Slexer *lexer);

struct Stok *
Slexer_tokenize_string
(struct Slexer *lexer);

struct Stok *
Slexer_tokenize_number
(struct Slexer *lexer);

struct Stok *
Slexer_tokenize_identifier
(struct Slexer *lexer);

struct Stok *
Slexer_tokenize_keyword
(struct Slexer *lexer);

#endif // SLEXER_H