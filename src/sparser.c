#include "sparser.h"

struct Sparser *
Sparser_new(void) {
    struct Sparser *parser = malloc(sizeof(struct Sparser));

    parser->ast = Sast_new();

    parser->lexer = Slexer_new();

    parser->token = Stok_new();
    parser->next_token = Stok_new();

    return parser;
}

struct Sparser *
Sparser_init
(struct Slexer *lexer) {
    struct Sparser *parser = Sparser_new();

    parser->lexer = lexer;

    return parser;
}

int 
Sparser_free
(struct Sparser *parser) {
    Slexer_free(parser->lexer);
    Stok_free(parser->token);
    Stok_free(parser->next_token);

    return 0;
}

struct Sast *
Sparser_parse_program
(struct Sparser *parser) {
    struct Sast *ast = Sast_new();

    parser->token = Slexer_get_next_token(parser->lexer);

    while (parser->token->type != EOF_TOK) {
        struct Sast *statement = Sparser_parse(parser);

        Sast_set_line(parser->lexer, statement);

        if (!statement) {
            struct Serror *error = Serror_set("SYNTAX_ERROR", "Expected statement", parser->lexer);
            Serror_syntax_error(error);
            return NULL;
        }

        Sast_add_child(ast, statement);
    }

    return ast;
}

struct Sast *
Sparser_parse(struct Sparser *parser) {
    if (parser->token->type == LET) {
        return Sparser_parse_assignment(parser);
    } 

    if (parser->token->type == PRINT_T) {
        return Sparser_parse_print(parser);
    }

    return Sparser_parse_additive_expression(parser);
}

struct Sast *
Sparser_parse_primary_expression
(struct Sparser *parser) {
    if (parser->token->type == NUMBER) {
        struct Sast *node = AST(AST_LITERAL, parser->token->value, parser->token->lexeme);

        Sast_set_line(parser->lexer, node);
        return node;
    }

    if (IS_TOK_EXPR_START(parser->token)) {
        struct Sast *node = AST(AST_IDENTIFIER, parser->token->value, parser->token->lexeme);

        Sast_set_line(parser->lexer, node);
        return node;
    }

    struct Serror *error = Serror_set("SYNTAX_ERROR", "Expected primary expression", parser->lexer);
    Serror_syntax_error(error);
    return NULL;
}

struct Sast *
Sparser_parse_additive_expression
(struct Sparser *parser) {
    struct Sast *left = Sparser_parse_multiplicative_expression(parser);

    while (parser->token->type == ADD || parser->token->type == SUB) {
        enum Stok_t op = parser->token->type;

        parser->token = Slexer_get_next_token(parser->lexer);
        struct Sast *right = Sparser_parse_multiplicative_expression(parser);

        if (!right) {
            struct Serror *error = Serror_set("SYNTAX_ERROR", "Expected multiplicative expression", parser->lexer);
            Serror_syntax_error(error);
            return NULL;
        }

        struct Sast *node = AST(AST_BINARY_EXPRESSION, 0, NULL);

        node->left = left;
        node->right = right;
        node->op = op;
        
        left = node;
    }

    Sast_set_line(parser->lexer, left);
    return left;
}

struct Sast *
Sparser_parse_multiplicative_expression
(struct Sparser *parser) {
    struct Sast *left = Sparser_parse_primary_expression(parser);

    parser->token = Slexer_get_next_token(parser->lexer);
    while (parser->token->type == MUL || parser->token->type == DIV) {
        enum Stok_t op = parser->token->type;

        parser->token = Slexer_get_next_token(parser->lexer);
        struct Sast *right = Sparser_parse_primary_expression(parser);

        if (!right) {
            struct Serror *error = Serror_set("SYNTAX_ERROR", "Expected primary expression", parser->lexer);
            Serror_syntax_error(error);
            return NULL;
        }

        struct Sast *node = AST(AST_BINARY_EXPRESSION, 0, NULL);

        node->left = left;
        node->right = right;
        node->op = op;
        
        left = node;

        parser->token = Slexer_get_next_token(parser->lexer);
    }

    Sast_set_line(parser->lexer, left);
    return left;
}

struct Sast *
Sparser_parse_assignment
(struct Sparser *parser) {
    struct Sast *node = AST(AST_ASSIGNMENT, 0, NULL);
    parser->token = Slexer_get_next_token(parser->lexer);

    if (parser->token->type == IDENTIFIER) {
        node->var_name = parser->token->lexeme;

    } else {
        struct Serror *error = Serror_set("SYNTAX_ERROR", "Expected identifier", parser->lexer);
        Serror_syntax_error(error);
        return NULL;
    }

    parser->token = Slexer_get_next_token(parser->lexer);

    if (parser->token->type == ASSIGN) {
        parser->token = Slexer_get_next_token(parser->lexer);

        node->var_value = Sparser_parse(parser);

        if (!is_expr(node->var_value)) {
            struct Serror *error = Serror_set("SYNTAX_ERROR", "Expected expression", parser->lexer);
            Serror_syntax_error(error);
            return NULL;
        }

        Sast_set_line(parser->lexer, node->var_value);
        
        Sast_set_line(parser->lexer, node);

        return node;
    } else {
        struct Serror *error = Serror_set("SYNTAX_ERROR", "Expected assignment operator", parser->lexer);
        Serror_syntax_error(error);
        return NULL;
    }

    return NULL;
}

struct Sast *
Sparser_parse_print
(struct Sparser *parser) {
    struct Sast *node = AST(AST_PRINT, 0, NULL);

    parser->token = Slexer_get_next_token(parser->lexer);

    node->print_value = Sparser_parse(parser);

    if (!is_expr(node->print_value)) {
        struct Serror *error = Serror_set("SYNTAX_ERROR", "Expected expression", parser->lexer);
        Serror_syntax_error(error);
        return NULL;
    }

    Sast_set_line(parser->lexer, node->print_value);
    return node;
}