#ifndef SPARSER_H
#define SPARSER_H

#include "slexer.h"
#include "sast.h"

struct Sparser {
    struct Sast *ast;

    struct Slexer *lexer;

    struct Stok *token;
    struct Stok *next_token;
};

struct Sparser *
Sparser_new(void);

struct Sparser *
Sparser_init
(struct Slexer *lexer);

int 
Sparser_free
(struct Sparser *parser);

struct Sast *
Sparser_parse_program
(struct Sparser *parser);

struct Sast *
Sparser_parse
(struct Sparser *parser);

struct Sast *
Sparser_parse_primary_expression
(struct Sparser *parser);

struct Sast *
Sparser_parse_additive_expression
(struct Sparser *parser);

struct Sast *
Sparser_parse_multiplicative_expression
(struct Sparser *parser);

struct Sast *
Sparser_parse_assignment
(struct Sparser *parser);

struct Sast *
Sparser_parse_print
(struct Sparser *parser);

#endif // SPARSER_H