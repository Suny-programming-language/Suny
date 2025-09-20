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

struct Sast* 
Sparser_parse_second_primary
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
Sparser_parse_not
(struct Sparser *parser);

struct Sast *
Sparser_parse_and
(struct Sparser *parser);

struct Sast *
Sparser_parse_or
(struct Sparser *parser);

struct Sast *
Sparser_parse_print
(struct Sparser *parser);

struct Sast *
Sparser_parse_function
(struct Sparser *parser);

struct Sast *
Sparser_parse_block_expression
(struct Sparser *parser);

struct Sast *
Sparser_parse_function_call_identifier
(struct Sparser *parser);

struct Sast *
Sparser_parse_block
(struct Sparser *parser);

struct Sast *
Sparser_parse_if_block
(struct Sparser *parser);

struct Sast *
Sparser_parse_if
(struct Sparser *parser);

struct Sast *
Sparser_parse_else_block
(struct Sparser *parser);

struct Sast *
Sparser_parse_return
(struct Sparser *parser);

struct Sast *
Sparser_parse_while
(struct Sparser *parser);

struct Sast *
Sparser_parse_list
(struct Sparser *parser);

struct Sast *
Sparser_parse_for
(struct Sparser *parser);

struct Sast *
Sparser_parse_class
(struct Sparser *parser);

struct Sast *
Sparser_parse_include
(struct Sparser *parser);

struct Sast *
Sparser_parse_anonymous_function
(struct Sparser *parser);

struct Sast *
Sparser_parse_loop
(struct Sparser *parser);

struct Sast *
Sparser_parse_variable_list
(struct Sparser *parser);

struct Sast *
Sparser_parse_import
(struct Sparser *parser);

struct Sast *
Sparser_parse_store_attribute
(struct Sparser *parser, struct Sast* object);

struct Sast *
Sparser_parse_attribute_expression
(struct Sparser *parser, struct Sast* object);

struct Sast *
Sparser_parse_store_index
(struct Sparser *parser, struct Sast* extract_obj);

struct Sast *
Sparser_parse_attribute
(struct Sparser *parser, struct Sast* object, struct Sast* attribute);

struct Sast *
Sparser_parse_function_call
(struct Sparser *parser, struct Sast *expr);

struct Sast *
Sparser_parse_extract
(struct Sparser *parser, struct Sast *extract_obj);

#endif // SPARSER_H