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
Sparser_parse_logic_expression
(struct Sparser *parser);

struct Sast *
Sparser_parse_parent_expression
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
Sparser_parse_comparison_expression
(struct Sparser *parser);

struct Sast *
Sparser_parse_let
(struct Sparser *parser);

struct Sast *
Sparser_parse_assignment
(struct Sparser *parser);

struct Sast *
Sparser_parse_print
(struct Sparser *parser);

struct Sast *
Sparser_parse_function
(struct Sparser *parser);

struct Sast *
Sparser_parse_function_call
(struct Sparser *parser);

struct Sast *
Sparser_parse_block
(struct Sparser *parser);

struct Sast *
Sparser_parse_if_block
(struct Sparser *parser);

struct Sast *
Sparser_parse_else_block
(struct Sparser *parser);

struct Sast *
Sparser_parse_return
(struct Sparser *parser);

struct Sast *
Sparser_parse_if
(struct Sparser *parser);

struct Sast *
Sparser_parse_while
(struct Sparser *parser);

struct Sast *
Sparser_parse_list
(struct Sparser *parser);

struct Sast *
Sparser_parse_extract
(struct Sparser *parser, struct Sast* extract_obj);

struct Sast *
Sparser_parse_store_index
(struct Sparser *parser, struct Sast* extract_obj);

#endif // SPARSER_H