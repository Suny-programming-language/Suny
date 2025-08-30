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
            Serror_parser("Expected statement", parser->lexer);
            return NULL;
        }

        Sast_add_child(ast, statement);
    }

    return ast;
}

struct Sast *
Sparser_parse(struct Sparser *parser) {
    if (parser->token->type == IDENTIFIER) {
        parser->next_token = Slexer_look_ahead(parser->lexer);

        if (parser->next_token->type == ASSIGN) {
            return Sparser_parse_assignment(parser);
        }
    }

    if (parser->token->type == RETURN) {
        return Sparser_parse_return(parser);
    }

    if (parser->token->type == BREAK) {
        struct Sast *node = AST(AST_BREAK, 0, NULL);

        parser->token = Slexer_get_next_token(parser->lexer);
        Sast_set_line(parser->lexer, node);
        return node;
    } 

    if (parser->token->type == CONTINUE) {
        struct Sast *node = AST(AST_CONTINUE, 0, NULL);

        parser->token = Slexer_get_next_token(parser->lexer);
        Sast_set_line(parser->lexer, node);
        return node;
    }

    if (parser->token->type == DO) {
        return Sparser_parse_block(parser);
    }

    if (parser->token->type == FOR) {
        return Sparser_parse_for(parser);
    }

    if (parser->token->type == FUNCTION) {
        return Sparser_parse_function(parser);
    }

    if (parser->token->type == WHILE) {
        return Sparser_parse_while(parser);
    }

    if (parser->token->type == LET) {
        return Sparser_parse_let(parser);
    }

    if (parser->token->type == IF) {
        return Sparser_parse_if(parser);
    }

    return Sparser_parse_logic_expression(parser);
}

struct Sast *
Sparser_parse_primary_expression
(struct Sparser *parser) {
    if (parser->token->type == LPAREN) {
        struct Sast *node = Sparser_parse_parent_expression(parser);

        parser->next_token = Slexer_look_ahead(parser->lexer);
        if (parser->next_token->type == LBRACKET) {
            return Sparser_parse_extract(parser, node);
        }

        Sast_set_line(parser->lexer, node);
        return node;
    }

    if (parser->token->type == TRUE_T) {
        struct Sast *node = AST(AST_TRUE, 1, NULL);
        Sast_set_line(parser->lexer, node);
        return node;
    }

    if (parser->token->type == FALSE_T) {
        struct Sast *node = AST(AST_FALSE, 0, NULL);
        Sast_set_line(parser->lexer, node);
        return node;
    }

    if (parser->token->type == IDENTIFIER) {
        parser->next_token = Slexer_look_ahead(parser->lexer);

        if (parser->next_token->type == LPAREN) {
            struct Sast *node = Sparser_parse_function_call(parser);

            parser->next_token = Slexer_look_ahead(parser->lexer);
            if (parser->next_token->type == LBRACKET) {
                return Sparser_parse_extract(parser, node);
            }

            return node;
        }

        struct Sast *node = AST(AST_IDENTIFIER, parser->token->value, parser->token->lexeme);

        Sast_set_line(parser->lexer, node);

        parser->next_token = Slexer_look_ahead(parser->lexer);
        if (parser->next_token->type == LBRACKET) {
            return Sparser_parse_extract(parser, node);
        }

        return node;
    }

    if (parser->token->type == LBRACKET) {
        struct Sast *node = Sparser_parse_list(parser);

        Sast_set_line(parser->lexer, node);

        parser->next_token = Slexer_look_ahead(parser->lexer);
        
        if (parser->next_token->type == LBRACKET) {
            return Sparser_parse_extract(parser, node);
        }

        return node;
    }

    if (parser->token->type == NUMBER) {
        struct Sast *node = AST(AST_LITERAL, parser->token->value, parser->token->lexeme);

        Sast_set_line(parser->lexer, node);

        parser->next_token = Slexer_look_ahead(parser->lexer);
        if (parser->next_token->type == LBRACKET) {
            Serror_parser("Numeric expression cannot be extracted", parser->lexer);
        }

        return node;
    }

    if (parser->token->type == STRING) {
        struct Sast *node = AST(AST_STRING_EXPRESSION, parser->token->value, parser->token->lexeme);

        Sast_set_line(parser->lexer, node);

        parser->next_token = Slexer_look_ahead(parser->lexer);
        if (parser->next_token->type == LBRACKET) {
            Serror_parser("String expression cannot be extracted", parser->lexer);
        }

        return node;
    }

    printf("%s\n", Stok_t_print(parser->token->type));
    Serror_parser("Expected primary expression", parser->lexer);
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
            Serror_parser("Expected multiplicative expression", parser->lexer);
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
            Serror_parser("Expected primary expression", parser->lexer);
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
Sparser_parse_let
(struct Sparser *parser) {
    struct Sast *node = AST(AST_ASSIGNMENT, 0, NULL);
    parser->token = Slexer_get_next_token(parser->lexer);

    if (parser->token->type == IDENTIFIER) {
        node->var_name = parser->token->lexeme;

    } else {
        Serror_parser("Expected identifier", parser->lexer);
        return NULL;
    }

    parser->token = Slexer_get_next_token(parser->lexer);

    if (parser->token->type == ASSIGN) {
        parser->token = Slexer_get_next_token(parser->lexer);

        node->var_value = Sparser_parse(parser);

        Sast_set_line(parser->lexer, node->var_value);
        Sast_set_line(parser->lexer, node);

        Sast_expected_expression(node->var_value);

        return node;
    } else {
        Serror_parser("Expected assignment", parser->lexer);
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

    Sast_set_line(parser->lexer, node->print_value);
    Sast_expected_expression(node->print_value);

    Sast_set_line(parser->lexer, node->print_value);
    return node;
}

struct Sast *
Sparser_parse_logic_expression
(struct Sparser *parser) {
    struct Sast *left = Sparser_parse_comparison_expression(parser);

    if (!left) {
        Serror_parser("Expected comparison expression", parser->lexer);
        return NULL;
    }

    if (parser->token->type == ASSIGN) {
        if (left->type == AST_EXTRACT) {
            return Sparser_parse_store_index(parser, left);
        }
    }

    return left;
}

struct Sast *
Sparser_parse_parent_expression
(struct Sparser *parser) {
    if (parser->token->type == LPAREN) {
        parser->token = Slexer_get_next_token(parser->lexer);

        struct Sast* node = Sparser_parse(parser);

        Sast_set_line(parser->lexer, node);
        Sast_expected_expression(node);

        if (parser->token->type == RPAREN) {
            return node;
        } else {
            Serror_parser("Expected closing parenthesis", parser->lexer);
            return NULL;
        }
    } else {
        Serror_parser("Expected opening parenthesis", parser->lexer);
        return NULL;
    }
    return NULL;
}

struct Sast *
Sparser_parse_comparison_expression
(struct Sparser *parser) {
    struct Sast *left = Sparser_parse_additive_expression(parser);

    if (!left) {
        Serror_parser("Expected additive expression", parser->lexer);
        return NULL;
    }

    while 
    (parser->token->type == EQUALS 
    || parser->token->type == NOT_EQUALS 
    || parser->token->type == BIGGER 
    || parser->token->type == SMALLER 
    || parser->token->type == BIGGER_EQUALS 
    || parser->token->type == SMALLER_EQUALS) {
        enum Stok_t op = parser->token->type;

        parser->token = Slexer_get_next_token(parser->lexer);
        struct Sast *right = Sparser_parse_additive_expression(parser);

        if (!right) {
            Serror_parser("Expected additive expression", parser->lexer);
            return NULL;
        }

        struct Sast *node = AST(AST_COMPARE_EXPRESSION, 0, NULL);

        node->left = left;
        node->right = right;
        node->op = op;
        
        left = node;
    }

    return left;
}

struct Sast *
Sparser_parse_assignment
(struct Sparser *parser) {
    struct Sast *node = AST(AST_ASSIGNMENT, 0, NULL);

    node->var_name = parser->token->lexeme;

    parser->token = Slexer_get_next_token(parser->lexer);

    if (parser->token->type == ASSIGN) {
        parser->token = Slexer_get_next_token(parser->lexer);

        node->var_value = Sparser_parse(parser);

        Sast_set_line(parser->lexer, node->var_value);
        Sast_expected_expression(node->var_value);
        Sast_set_line(parser->lexer, node);

        return node;
    } else {
        Serror_parser("Expected assignment", parser->lexer);
    }   

    return NULL;
}

struct Sast *
Sparser_parse_function
(struct Sparser *parser) {
    struct Sast *node = AST(AST_FUNCTION_STATEMENT, 0, NULL);

    parser->token = Slexer_get_next_token(parser->lexer);
    if (parser->token->type == IDENTIFIER) {
        node->lexeme = parser->token->lexeme;

        parser->token = Slexer_get_next_token(parser->lexer);

        if (parser->token->type == LPAREN) {
            while (parser->token->type != RPAREN) {
                parser->token = Slexer_get_next_token(parser->lexer);
                if (parser->token->type == IDENTIFIER) {
                    Sast_set_para(node, parser->token->lexeme);
                    node->args_count++;
                    node->is_having_params = 1;
                    parser->token = Slexer_get_next_token(parser->lexer);
                    if (parser->token->type == COMMA) {
                        continue;
                    } else if (parser->token->type == RPAREN) {
                        break;
                    } else {
                        Serror_parser("Expected comma or closing parenthesis", parser->lexer);
                        return NULL;
                    }
                } else if (parser->token->type == RPAREN) {
                    break;
                } else {
                    Serror_parser("Expected identifier or closing parenthesis", parser->lexer);
                    return NULL;
                }
            }

            parser->token = Slexer_get_next_token(parser->lexer);
            if (parser->token->type == DO) {
                struct Sast *block = Sparser_parse_block(parser);
                node->body = block->block;
                node->body_size = block->block_size;
                node->block_count = block->block_count;
                node->block_size = block->block_size;
            } else {
                Serror_parser("Expected 'do'", parser->lexer);
                return NULL;
            }

            Sast_set_line(parser->lexer, node);
            return node;
        } else {
            Serror_parser("Expected opening parenthesis", parser->lexer);
            return NULL;
        }
    } else {
        Serror_parser("Expected identifier", parser->lexer);
        return NULL;
    }

    return node;
}

struct Sast *
Sparser_parse_function_call
(struct Sparser *parser) {
    struct Sast *node = AST(AST_FUNCTION_CALL_EXPRESSION, 0, NULL);

    if (parser->token->type == IDENTIFIER) {
        node->lexeme = parser->token->lexeme;

        parser->token = Slexer_get_next_token(parser->lexer);

        if (parser->token->type == LPAREN) {
            parser->token = Slexer_get_next_token(parser->lexer);

            while (parser->token->type != RPAREN) {
                struct Sast *expr = Sparser_parse(parser);
                
                Sast_set_line(parser->lexer, expr);
                Sast_expected_expression(expr);
                Sast_add_args(node, expr);

                if (parser->token->type == COMMA) {
                    parser->token = Slexer_get_next_token(parser->lexer);
                } else if (parser->token->type == RPAREN) {
                    break;
                } else {
                    Serror_parser("Expected comma or closing parenthesis", parser->lexer);
                    return NULL;
                }
            }

            Sast_set_line(parser->lexer, node);
            return node;
        } else {
            Serror_parser("Expected opening parenthesis", parser->lexer);
            return NULL;
        }
    } else {
        Serror_parser("Expected identifier", parser->lexer);
        return NULL;
    }

    Serror_parser("Expected identifier", parser->lexer);
    return NULL;
}   

struct Sast *
Sparser_parse_block
(struct Sparser *parser) {
    struct Sast *node = AST(AST_BLOCK, 0, NULL);

    if (parser->token->type != DO) {
        Serror_parser("Expected 'do'", parser->lexer);
        return NULL;
    }

    parser->token = Slexer_get_next_token(parser->lexer);

    while (parser->token->type != END) {
        struct Sast *stmt = Sparser_parse(parser);
        Sast_set_line(parser->lexer, node);
        Sast_add_block(node, stmt);

        node->block_size++;

        if (!stmt) {
            Serror_parser("Expected statement", parser->lexer);
            return NULL;
        }
    }

    parser->token = Slexer_get_next_token(parser->lexer);

    return node;
}

struct Sast *
Sparser_parse_return
(struct Sparser *parser) {
    struct Sast *node = AST(AST_RETURN_STATEMENT, 0, NULL);

    parser->token = Slexer_get_next_token(parser->lexer);

    struct Sast *expr = Sparser_parse(parser);

    Sast_set_line(parser->lexer, expr);
    Sast_expected_expression(expr);

    node->ret_val = expr;

    return node;
}

struct Sast *
Sparser_parse_if
(struct Sparser *parser) {
    struct Sast *node = AST(AST_IF, 0, NULL);

    parser->token = Slexer_get_next_token(parser->lexer);

    struct Sast *expr = Sparser_parse(parser);

    Sast_set_line(parser->lexer, expr);
    Sast_expected_expression(expr);

    node->condition = expr;

    struct Sast *block = Sparser_parse_if_block(parser);

    node->if_body = block->block;
    node->if_body_size = block->block_size;

    return node;
}

struct Sast *
Sparser_parse_while
(struct Sparser *parser) {
    struct Sast *node = AST(AST_WHILE, 0, NULL);

    parser->token = Slexer_get_next_token(parser->lexer);

    struct Sast *expr = Sparser_parse(parser);

    Sast_set_line(parser->lexer, expr);
    Sast_expected_expression(expr);

    node->condition = expr;

    struct Sast *block = Sparser_parse_block(parser);

    node->body = block->block;
    node->body_size = block->block_size;

    return node;
}

struct Sast *
Sparser_parse_if_block
(struct Sparser *parser) {
    struct Sast *node = AST(AST_BLOCK, 0, NULL);

    if (parser->token->type != THEN) {
        Serror_parser("Expected 'then'", parser->lexer);
        return NULL;
    }

    parser->token = Slexer_get_next_token(parser->lexer);

    while (parser->token->type != END) {
        struct Sast *stmt = Sparser_parse(parser);
        Sast_set_line(parser->lexer, node);
        Sast_add_block(node, stmt);

        node->block_size++;

        if (!stmt) {
            Serror_parser("Expected statement", parser->lexer);
            return NULL;
        }
    }

    parser->token = Slexer_get_next_token(parser->lexer);

    return node;
}

struct Sast *
Sparser_parse_else_block
(struct Sparser *parser) {
    struct Sast *node = AST(AST_BLOCK, 0, NULL);

    if (parser->token->type != ELSE) {
        Serror_parser("Expected 'else'", parser->lexer);
        return NULL;
    }

    parser->token = Slexer_get_next_token(parser->lexer);

    while (parser->token->type != END) {
        struct Sast *stmt = Sparser_parse(parser);
        Sast_set_line(parser->lexer, node);
        Sast_add_block(node, stmt);

        node->block_size++;

        if (!stmt) {
            Serror_parser("Expected statement", parser->lexer);
            return NULL;
        }
    }

    parser->token = Slexer_get_next_token(parser->lexer);

    return node;
}

struct Sast *
Sparser_parse_list
(struct Sparser *parser) {
    struct Sast *node = AST(AST_LIST, 0, NULL);

    parser->token = Slexer_get_next_token(parser->lexer);

    while (parser->token->type != RBRACKET) {
        struct Sast *stmt = Sparser_parse(parser);

        Sast_set_line(parser->lexer, node);
        Sast_expected_expression(stmt);
        Sast_add_element(node, stmt);

        if (parser->token->type == COMMA) {
            parser->token = Slexer_get_next_token(parser->lexer);
        } else if (parser->token->type == RBRACKET) {
            break;
        } else {
            Serror_parser("Expected comma or closing parenthesis", parser->lexer);
            return NULL;
        }
    }

    return node;
}

struct Sast *
Sparser_parse_extract(struct Sparser *parser, struct Sast *extract_obj) {
    struct Sast *node = AST(AST_EXTRACT, 0, NULL);

    node->extract_obj = extract_obj;

    parser->token = Slexer_get_next_token(parser->lexer); // eat the opening bracket

    if (parser->token->type != LBRACKET) {
        Serror_parser("Expected opening bracket '['", parser->lexer);
        return NULL;
    }

    parser->token = Slexer_get_next_token(parser->lexer);
    
    struct Sast *expr = Sparser_parse(parser);
    Sast_set_line(parser->lexer, expr);
    Sast_expected_expression(expr);

    node->extract_value = expr;

    if (parser->token->type != RBRACKET) {
        Serror_parser("Expected closing bracket ']'", parser->lexer);
        return NULL;
    }

    parser->next_token = Slexer_look_ahead(parser->lexer);

    if (parser->next_token->type == LBRACKET) {
        return Sparser_parse_extract(parser, node);
    }

    return node;
}

struct Sast *
Sparser_parse_store_index
(struct Sparser *parser, struct Sast* extract_obj) {
    struct Sast *node = AST(AST_STORE_INDEX, 0, NULL);

    node->extract_obj = extract_obj;

    parser->token = Slexer_get_next_token(parser->lexer);

    struct Sast *expr = Sparser_parse(parser);
    Sast_set_line(parser->lexer, expr);
    Sast_expected_expression(expr);

    node->extract_value = expr;

    return node;
}

struct Sast *
Sparser_parse_for
(struct Sparser *parser) {
    struct Sast *node = AST(AST_FOR, 0, NULL);

    parser->token = Slexer_get_next_token(parser->lexer);

    if (parser->token->type != IDENTIFIER) {
        Serror_parser("Expected identifier", parser->lexer);
        return NULL;
    }

    node->lexeme = parser->token->lexeme;

    parser->token = Slexer_get_next_token(parser->lexer);

    if (parser->token->type != IN_T) {
        Serror_parser("Expected 'in'", parser->lexer);
        return NULL;
    }

    parser->token = Slexer_get_next_token(parser->lexer);

    struct Sast *expr = Sparser_parse(parser);
    Sast_set_line(parser->lexer, expr);
    Sast_expected_expression(expr);

    node->expr = expr;

    struct  Sast *block = Sparser_parse_block(parser);

    node->block = block->block;
    node->block_size = block->block_size;

    return node;
}