#include "scompile.h"

struct Scope
new_scope(void) {
    struct Scope scope;
    scope.name = NULL;
    scope.address = 0;
    return scope;
}

struct Scompiler*
Scompiler_new(void) {
    struct Scompiler *compiler = malloc(sizeof(struct Scompiler));
    compiler->scope_index = 0;
    compiler->scope_size = 1024;
    compiler->address = 0;
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
        case AST_ASSIGNMENT:
            return Scompile_assignment(ast, compiler);
        case AST_PRINT:
            return Scompile_print(ast, compiler);
        default:
            printf("Unknown ast type");
            return NULL;
    }

    return NULL;
}

struct Scode*
Scompile_program
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *code = Scode_new();

    PUSH(code, PROGRAM_START);

    for (int i = 0; i < ast->child_count; i++) {
        struct Scode *child = Scompile(ast->children[i], compiler);
        INSERT(code, child);
    }

    PUSH(code, PROGRAM_END);

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
    struct Scode *code = Scode_new(); 

    char* name = ast->lexeme;

    for (int i = 0; i < compiler->scope_index; i++) {
        struct Scope scope = compiler->scope[i];

        if (strcmp(scope.name, name) == 0) {
            byte_t address = scope.address;

            PUSH(code, LOAD_GLOBAL);
            PUSH(code, address);

            return code;
        }
    }

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

struct Scode*
Scompile_assignment
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *code = Scode_new();
    struct Scode *value = Scompile(ast->var_value, compiler);

    struct Scope scope = new_scope();

    scope.name = ast->var_name;
    scope.address = ++compiler->address;

    compiler->scope[compiler->scope_index++] = scope;

    byte_t address = scope.address;

    INSERT(code, value);

    PUSH(code, STORE_GLOBAL);
    PUSH(code, address);

    return code;
}

struct Scode*
Scompile_print
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *code = Scompile(ast->print_value, compiler);
    
    PUSH(code, PRINT);

    return code;
}