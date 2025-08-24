#include "scompile.h"

struct Scompiler*
Scompiler_new(void) {
    struct Scompiler *compiler = malloc(sizeof(struct Scompiler));
    compiler->scope_index = 0;
    compiler->scope_size = 1024;
    return compiler;
}

struct Scode*
Scompile
(struct Sast *ast, struct Scompiler *compiler) {
    switch(ast->type) {
        case AST_PROGRAM:
            return Scompile_program(ast, compiler);
        case AST_BINARY_EXPRESSION:
            return Scompile_binary_expression(ast, compiler);
        case AST_IDENTIFIER:
            return Scompile_identifier(ast, compiler);
        case AST_LITERAL:
            return Scompile_literal(ast, compiler);
        default:
            return NULL;
    }

    return NULL;
}

struct Scode*
Scompile_program
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *code = Scode_new();

    for (int i = 0; i < ast->child_count; i++) {
        struct Scode *child = Scompile(ast->children[i], compiler);
        INSERT(code, child);
    }

    return code;
}

struct Scode*
Scompile_binary_expression
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *code = Scode_new();

    struct Scode *left = Scompile(ast->left, compiler);
    struct Scode *right = Scompile(ast->right, compiler);

    INSERT(code, left);
    INSERT(code, right);

    switch(ast->op) {
        case ADD:
            PUSH(code, BINARY_ADD);
            break;
        case SUB:
            PUSH(code, BINARY_SUB);
            break;
        case MUL:
            PUSH(code, BINARY_MUL);
            break;
        case DIV:
            PUSH(code, BINARY_DIV);
            break;
        default:
            break;
    }

    return code;
}

struct Scode*
Scompile_identifier
(struct Sast *ast, struct Scompiler *compiler) {
    return NULL;
}

struct Scode*
Scompile_literal
(struct Sast *ast, struct Scompiler *compiler) {
    float value = ast->value;

    struct Scode *code = Scode_new();

    PUSH(code, PUSH_FLOAT);

    unsigned char float_code[4];
    memcpy(float_code, &value, sizeof(float));

    PUSH(code, float_code[0]);
    PUSH(code, float_code[1]);
    PUSH(code, float_code[2]);
    PUSH(code, float_code[3]);

    return code;
}