#include "sast.h"

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
        case AST_FUNCTION_CALL_EXPRESSION:
            printf("Function Call\n");
            break;
        case AST_FUNCTION_STATEMENT:
            printf("Function\n");
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
    sast->is_assign = 0;
    sast->has_until = 0;
    sast->has_times = 0;
    
    sast->value = 0;
    sast->child_count = 0;
    sast->child_capacity = 0;

    sast->children = NULL;

    sast->print_value = NULL;

    sast->params = calloc(MAX_STATEMENT_SIZE, sizeof(struct Sast *));
    sast->param_count = 0;

    sast->body = calloc(MAX_STATEMENT_SIZE, sizeof(struct Sast *));

    sast->left = NULL;
    sast->right = NULL;
    sast->op = NULL_TOK;

    sast->condition = NULL;
    sast->if_body = calloc(MAX_STATEMENT_SIZE, sizeof(struct Sast *));
    sast->else_body = calloc(MAX_STATEMENT_SIZE, sizeof(struct Sast *));
    sast->if_body_size = 0;
    sast->else_body_size = 0;

    sast->body_size = 0;
    sast->is_having_params = 0;

    sast->block_count = 0;
    sast->block_size = 0;
    sast->block_capacity = 0;

    sast->block = calloc(MAX_STATEMENT_SIZE, sizeof(struct Sast *));

    sast->args_count = 0;

    sast->param_names = calloc(MAX_STATEMENT_SIZE, sizeof(char *));

    sast->var_name = NULL;
    sast->var_value = NULL;

    sast->print_value = NULL;

    sast->ast_line = 0;
    sast->ast_column = 0;

    sast->lexer = Slexer_new();

    sast->ret_val = NULL;

    sast->list_count = 0;
    sast->list_capacity = 1024;

    sast->list = calloc(sast->list_capacity, sizeof(struct Sast *));

    sast->extract_obj = NULL;
    sast->extract_value = NULL;

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
Sast_add_block
(struct Sast *parent, struct Sast *child) {
    if (parent->block_capacity == 0) {
    
        parent->block_capacity = 4;
    
        parent->block = (struct Sast **)malloc(sizeof(struct Sast *) * parent->block_capacity);
    } else if (parent->block_count >= parent->block_capacity) {
    
        parent->block_capacity *= 2;
    
        parent->block = (struct Sast **)realloc(parent->block, sizeof(struct Sast *) * parent->block_capacity);
    }

    parent->block[parent->block_count++] = child;

    return 0;
}

struct Sast* 
Sast_get_child
(struct Sast *sast, int index) {
    return sast->children[index];
}

int
Sast_set_para
(struct Sast *func, char* param_names) {
    func->param_names[func->param_count++] = param_names;
    return 0;
}

int
Sast_add_args
(struct Sast *func, struct Sast *param) {
    func->params[func->param_count++] = param;
    return 0;
}

struct Sast*
Sast_add_element(struct Sast *list, struct Sast *element) {
    if (list->list_capacity == 0) {
        list->list_capacity = 4;
        list->list = (struct Sast **)malloc(sizeof(struct Sast *) * list->list_capacity);
    } else if (list->list_count >= list->list_capacity) {
        list->list_capacity *= 2;
        list->list = (struct Sast **)realloc(list->list, sizeof(struct Sast *) * list->list_capacity);
    }

    list->list[list->list_count++] = element;
    return list;
}