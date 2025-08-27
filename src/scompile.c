#include "scompile.h"

struct Scope
new_scope(void) {
    struct Scope scope;
    scope.name = NULL;
    scope.address = 0;
    scope.args_size = 0;

    return scope;
}

int
add_scope
(struct Scompiler *compiler, char *name, int address, int args_size) {
    struct Scope scope = new_scope();

    for (int i = 0; i < compiler->scope_index; i++) {
        if (strcmp(compiler->scope[i].name, name) == 0) {
            return compiler->scope[i].address;
        }
    }

    scope.name = name;
    scope.address = address;
    scope.args_size = args_size;
    
    compiler->scope[compiler->scope_index++] = scope;
    return address;
}

int
find_scope
(struct Scompiler *compiler, char *name) {
    for (int i = 0; i < compiler->scope_index; i++) {
        struct Scope scope = compiler->scope[i];
        if (strcmp(scope.name, name) == 0) {
            return scope.address;
        }
    }
    return NOT_FOUND;
}

struct Scope
find_scope_obj
(struct Scompiler *compiler, char *name) {
    for (int i = 0; i < compiler->scope_index; i++) {
        struct Scope scope = compiler->scope[i];
        if (strcmp(scope.name, name) == 0) {
            return scope;
        }
    }
    
    printf("Scope not found: %s\n", name);
    return new_scope();
}

int
remove_scope(struct Scompiler *compiler, char *name) {
    for (int i = 0; i < compiler->scope_index; i++) {
        struct Scope scope = compiler->scope[i];
        if (strcmp(scope.name, name) == 0) {
            scope.name = NULL;
            scope.address = 0;
            return 0;
        }
    }
    return NOT_FOUND;
}

struct Scompiler*
Scompiler_new(void) {
    struct Scompiler *compiler = malloc(sizeof(struct Scompiler));
    compiler->scope_index = 0;
    compiler->scope_size = 1024;
    compiler->address = ADDRESS_START;

    compiler->is_in_block = 0;
    compiler->is_in_class = 0;
    compiler->is_in_func = 0;
    
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
        case AST_COMPARE_EXPRESSION:
            return Scompile_comparison(ast, compiler);
        case AST_FUNCTION_CALL_EXPRESSION:
            return Scompile_function_call(ast, compiler);
        case AST_FUNCTION_STATEMENT:
            return Scompile_function(ast, compiler);
        case AST_RETURN_STATEMENT:
            return Scompile_return(ast, compiler);
        default:
            struct Serror *error = Serror_set("COMPILER_ERROR", "Unknown AST type", ast->lexer);
            Serror_syntax_error(error);
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
            struct Serror *error = Serror_set("COMPILER_ERROR", "Unknown operator", ast->lexer);
            Serror_syntax_error(error);
            break;
    }

    return code;
}

struct Scode*
Scompile_identifier
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *code = Scode_new(); 

    int address = find_scope(compiler, ast->lexeme);

    if (address == NOT_FOUND) {
        struct Serror *error = Serror_set("COMPILER_ERROR", "Undefined variable", ast->lexer);
        Serror_syntax_error(error);
    } else {
        PUSH(code, LOAD_GLOBAL);
        PUSH(code, address);
    }

    return code;
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
    struct Scope scope = new_scope();

    struct Scode *code = Scode_new();
    struct Scode *value = Scompile(ast->var_value, compiler);
    int address = ++compiler->address;

    address = add_scope(compiler, ast->var_name, address, 0);

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

struct Scode*
Scompile_comparison
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *code = Scode_new();

    struct Scode *left = Scompile(ast->left, compiler);
    struct Scode *right = Scompile(ast->right, compiler);

    byte_t opcode;

    switch (ast->op) {
        case BIGGER:
            opcode = BINARY_BIGGER;
            break;
        case SMALLER:
            opcode = BINARY_SMALLER;
            break;
        case EQUALS:
            opcode = BINARY_EQUAL;
            break;
        case BIGGER_EQUALS:
            opcode = BINARY_BIGGER_EQUAL;
            break;
        case SMALLER_EQUALS:
            opcode = BINARY_SMALLER_EQUAL;
            break;
        case NOT_EQUALS:
            opcode = BINARY_NOT_EQUAL;
            break;
        default:
            struct Serror *error = Serror_set("COMPILER_ERROR", "Unknown operator", ast->lexer);
            Serror_syntax_error(error);
            return NULL;
    }

    INSERT(code, left);
    INSERT(code, right);
    PUSH(code, opcode);

    return code;
}

struct Scode*
Scompile_function
(struct Sast *ast, struct Scompiler *compiler) {
    int address = ++compiler->address;

    byte_t faddress = address;
    byte_t fargs_count = ast->args_count;

    add_scope(compiler, ast->lexeme, address, ast->args_count);

    struct Scode *code = Scode_new();
    struct Scode *body = Scompile_body_func(ast->body, compiler, ast->body_size, ast->param_names, ast->args_count);

    PUSH(code, MAKE_FUNCTION);
    PUSH(code, faddress);
    PUSH(code, fargs_count);

    INSERT(code, body);

    PUSH(code, END_FUNCTION);

    return code;
}

struct Scode*
Scompile_function_call
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *code = Scode_new();

    struct Scope scope = find_scope_obj(compiler, ast->lexeme);
    int address = scope.address;
    int args_size = scope.args_size;

    if (args_size != ast->param_count) {
        struct Serror *error = Serror_set("COMPILER_ERROR", "Wrong number of arguments", ast->lexer);
        Serror_syntax_error(error);
    }

    if (address == NOT_FOUND) {
        struct Serror *error = Serror_set("COMPILER_ERROR", "Undefined function", ast->lexer);
        Serror_syntax_error(error);
    }

    Sreverse((void **) ast->params, ast->param_count);
    struct Scode *param = Scompile_block(ast->params, compiler, ast->param_count);
    
    INSERT(code, param);

    PUSH(code, LOAD_GLOBAL);
    PUSH(code, address);

    PUSH(code, FUNCTION_CALL);
    return code;
}

struct Scode*
Scompile_block
(struct Sast **block, struct Scompiler *compiler, int block_size) {
    struct Scode *code = Scode_new();

    for (int i = 0; i < block_size; i++) {
        struct Scode *child = Scompile(block[i], compiler);
        INSERT(code, child);
    }

    return code;
}

struct Scode*
Scompile_body_func
(struct Sast **block, struct Scompiler *compiler, int block_size, char **args, int args_size) {
    struct Scode *code = Scode_new();

    compiler->is_in_func = 1;

    int args_address = 0;
    for (int i = 0; i < args_size; i++) {
        add_scope(compiler, args[i], args_address++, 0);
    }

    for (int i = 0; i < block_size; i++) {
        struct Scode *child = Scompile(block[i], compiler);
        INSERT(code, child);
    }

    int address = 0;
    for (int i = 0; i < args_size; i++) {
        remove_scope(compiler, args[i]);
    }

    compiler->is_in_func = 0;

    return code;
}

struct Scode*
Scompile_return
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *code = Scompile(ast->ret_val, compiler);

    if (compiler->is_in_func == 0) {
        struct Serror *error = Serror_set("COMPILER_ERROR", "Return outside of function", ast->lexer);
        Serror_syntax_error(error);
    }

    PUSH(code, RETURN_TOP);
    return code;
}