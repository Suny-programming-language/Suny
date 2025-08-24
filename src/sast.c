#include "sast.h"

int Sast_set_line(struct Slexer *lexer, struct Sast *sast) {
    sast->ast_line = lexer->line;
    sast->ast_column = lexer->column;
    sast->lexer = lexer;
    return 0;
}

struct Sast* 
Sast_new(void) {
    struct Sast *sast = malloc(sizeof(struct Sast));
    sast->type = AST_NULL;
    sast->lexeme = NULL;
    
    sast->value = 0;
    sast->child_count = 0;
    sast->child_capacity = 0;

    sast->children = NULL;

    sast->print_value = NULL;

    sast->left = NULL;
    sast->right = NULL;
    sast->op = NULL_TOK;

    sast->var_name = NULL;
    sast->var_value = NULL;

    sast->print_value = NULL;

    sast->ast_line = 0;
    sast->ast_column = 0;

    sast->lexer = Slexer_new();

    return sast;
}

struct Sast* 
Sast_init
(enum Sast_t type, float value, char *lexeme) {
    struct Sast *sast = Sast_new();

    sast->type = type;
    sast->value = value;
    sast->lexeme = lexeme;

    return sast;
}

int 
Sast_free
(struct Sast *sast) {
    if (sast == NULL) return 0;

    if (sast->lexeme != NULL) {
        free(sast->lexeme);
    }

    for (int i = 0; i < sast->child_count; i++) {
        Sast_free(sast->children[i]);
    }

    if (sast->children != NULL) {
        free(sast->children);
    }

    free(sast);

    return 1;
}

int 
Sast_add_child
(struct Sast *parent, struct Sast *child) {
    if (parent->child_capacity == 0) {
    
        parent->child_capacity = 4;
    
        parent->children = (struct Sast **)malloc(sizeof(struct Sast *) * parent->child_capacity);
    
    } else if (parent->child_count >= parent->child_capacity) {
    
        parent->child_capacity *= 2;
    
        parent->children = (struct Sast **)realloc(parent->children, sizeof(struct Sast *) * parent->child_capacity);
    }

    parent->children[parent->child_count++] = child;

    return 0;
}

int 
Sast_print
(struct Sast *sast) {
    switch(sast->type) {
        case AST_PROGRAM:
            printf("Program\n");
            break;
        case AST_BLOCK:
            printf("Block\n");
            break;
        case AST_STATEMENT:
            printf("Statement\n");
            break;
        case AST_EXPRESSION:
            printf("Expression\n");
            break;
        case AST_ASSIGNMENT:
            printf("Assignment\n");
            break;
        case AST_IF:
            printf("If\n");
            break;
        case AST_WHILE:
            printf("While\n");
            break;
        case AST_DO_LOOP:
            printf("Do Loop\n");
            break;
        case AST_FOR:
            printf("For\n");
            break;
        case AST_BINARY_EXPRESSION:
            printf("Binary Expression\n");
            printf("Operator: %s\n", Stok_t_print(sast->op));
            Sast_print(sast->left);
            Sast_print(sast->right);
            break;
        case AST_IDENTIFIER:
            printf("Identifier ");
            printf("Lexeme: %s\n", Stok_t_print(sast->type));
            break;
        case AST_LITERAL:
            printf("Literal\n");
            break;
        case AST_STRING_EXPRESSION:
            printf("String Expression\n");
            break;
        case AST_NULL:
            printf("Null\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }

    return 0;
}