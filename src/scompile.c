#include "scompile.h"

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
        case AST_STRING_EXPRESSION:
            return Scompile_string(ast, compiler);
        case AST_IF:
            return Scompile_if(ast, compiler);
        case AST_WHILE:
            return Scompile_while(ast, compiler);
        case AST_BREAK:
            return Scompile_break(ast, compiler);
        case AST_CONTINUE:
            return Scompile_continue(ast, compiler);
        case AST_LIST:
            return Scompile_list(ast, compiler);
        case AST_EXTRACT:
            return Scompile_extract(ast, compiler);
        case AST_STORE_INDEX:
            return Scompile_store_index(ast, compiler);
        case AST_FOR:
            return Scompile_for(ast, compiler);
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

    if (compiler->is_in_func) {
        address = find_scope_local(compiler, ast->lexeme);
        if (address == NOT_FOUND) {
            struct Serror *error = Serror_set("COMPILER_ERROR", "Undefined variable", ast->lexer);
            Serror_syntax_error(error);
        }

        PUSH(code, LOAD_GLOBAL);
        PUSH(code, address);
        return code;
    }

    if (address == NOT_FOUND) {
        if (address == NOT_FOUND) {
            struct Serror *error = Serror_set("COMPILER_ERROR", "Undefined variable", ast->lexer);
            Serror_syntax_error(error);
        }
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

    int found = find_scope(compiler, ast->var_name);

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
    int found = find_scope(compiler, ast->lexeme);

    if (found == NOT_FOUND) {
        struct Serror *error = Serror_set("COMPILER_ERROR", "Undefined function", ast->lexer);
        Serror_syntax_error(error);
    }

    int address = scope.address;
    int args_size = scope.args_size;

    if (args_size != ast->param_count) {
        struct Serror *error = Serror_set("COMPILER_ERROR", "Wrong number of arguments", ast->lexer);
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
        add_scope_local(compiler, args[i], args_address++, 0);
    }

    for (int i = 0; i < block_size; i++) {
        struct Scode *child = Scompile(block[i], compiler);
        INSERT(code, child);
    }

    int address = 0;
    for (int i = 0; i < args_size; i++) {
        remove_scope_local(compiler, args[i]);
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

struct Scode*
Scompile_string
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *code = Scode_new();

    char* string = ast->lexeme;

    int size = 0;

    unsigned char cstring[MAX_IDENTIFIER_SIZE];

    for (int i = 0; string[i] != '\0'; i++) {
        cstring[i] = string[i];
        ++size;
    }

    cstring[size] = '\0';

    PUSH(code, PUSH_STRING);

    PUSH(code, size);

    for (int i = 0; i < size; i++) {
        PUSH(code, cstring[i]);
    }

    return code;
}

struct Scode*
Scompile_if
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *conditon = Scompile(ast->condition, compiler);
    struct Scode *if_body = Scompile_block(ast->if_body, compiler, ast->if_body_size);

    struct Scode *code = Scode_new();

    int end_address = creat_label(compiler);

    INSERT(code, conditon);

    PUSH(code, POP_JUMP_IF_FALSE);
    PUSH(code, end_address);

    INSERT(code, if_body);

    PUSH(code, ADD_LABEL);
    PUSH(code, end_address);

    return code;
}

struct Scode*
Scompile_while
(struct Sast *ast, struct Scompiler *compiler) {
    compiler->is_in_loop = 1;

    int while_start = creat_label(compiler);
    int while_end = creat_label(compiler);

    Scompile_add_loop(compiler, while_start, while_end);

    struct Scode *conditon = Scompile(ast->condition, compiler);
    struct Scode *while_body = Scompile_block(ast->body, compiler, ast->body_size);

    Scompile_pop_loop(compiler);

    compiler->is_in_loop = 0;

    struct Scode *code = Scode_new();

    PUSH(code, ADD_LABEL);
    PUSH(code, while_start);

    INSERT(code, conditon);

    PUSH(code, POP_JUMP_IF_FALSE);
    PUSH(code, while_end);

    INSERT(code, while_body);

    PUSH(code, JUMP_TO);
    PUSH(code, while_start);

    PUSH(code, ADD_LABEL);
    PUSH(code, while_end);

    return code;
}


struct Scode*
Scompile_break
(struct Sast *ast, struct Scompiler *compiler) {
    if (!compiler->is_in_loop) {
        struct Serror *error = Serror_set("COMPILER_ERROR", "Break outside of loop", ast->lexer);
        Serror_syntax_error(error);
    }

    struct Scode *code = Scode_new();
    struct loop_stack loop = Scompile_get_loop(compiler);
    int address = loop.break_label;
    PUSH(code, JUMP_TO);
    PUSH(code, address);
    return code;
}

struct Scode*
Scompile_continue
(struct Sast *ast, struct Scompiler *compiler) {
    if (!compiler->is_in_loop) {
        struct Serror *error = Serror_set("COMPILER_ERROR", "Continue outside of loop", ast->lexer);
        Serror_syntax_error(error);
    }

    struct Scode *code = Scode_new();
    struct loop_stack loop = Scompile_get_loop(compiler);
    int address = loop.continue_label;
    PUSH(code, JUMP_TO);
    PUSH(code, address);
    return code;
}

struct Scode*
Scompile_list
(struct Sast *ast, struct Scompiler *compiler) {
    Sreverse((void **) ast->list, ast->list_count);
    struct Scode *code = Scompile_block(ast->list, compiler, ast->list_count);

    PUSH(code, BUILD_LIST);
    PUSH(code, ast->list_count);

    return code;
}


struct Scode*
Scompile_extract
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *extract = Scompile(ast->extract_obj, compiler);
    struct Scode *value = Scompile(ast->extract_value, compiler);

    struct Scode *code = Scode_new();

    INSERT(code, extract);
    INSERT(code, value);

    PUSH(code, LOAD_ITEM);

    return code;
}

struct Scode*
Scompile_store_index
(struct Sast *ast, struct Scompiler *compiler) {
    struct Scode *value = Scompile(ast->extract_value, compiler);
    struct Scode *obj = Scompile(ast->extract_obj->extract_obj, compiler);
    struct Scode *index = Scompile(ast->extract_obj->extract_value, compiler);

    struct Scode *code = Scode_new();

    INSERT(code, obj);
    INSERT(code, index);
    INSERT(code, value);

    PUSH(code, STORE_ITEM);

    return code;
}

struct Scode*
Scompile_for
(struct Sast *ast, struct Scompiler *compiler) {
    int iden = ++compiler->address;
    int loop_start = creat_label(compiler);
    int loop_end = creat_label(compiler);

    add_scope(compiler, ast->lexeme, iden, 0);

    struct Scode *for_body = Scompile_block(ast->block, compiler, ast->block_size);
    struct Scode *iter = Scompile(ast->expr, compiler);

    struct Scode *code = Scode_new();

    INSERT(code, iter);

    PUSH(code, STORE_GLOBAL);
    PUSH(code, __iter__a);

    PUSH(code, PUSH_FLOAT);
    PUSH(code, '\x00');
    PUSH(code, '\x00');
    PUSH(code, '\x00');
    PUSH(code, '\x00');

    PUSH(code, STORE_GLOBAL);
    PUSH(code, __i__a);

    PUSH(code, ADD_LABEL);
    PUSH(code, loop_start);

    PUSH(code, LOAD_GLOBAL);
    PUSH(code, __i__a);

    PUSH(code, LOAD_GLOBAL);
    PUSH(code, __iter__a);

    PUSH(code, LEN_OF);

    PUSH(code, BINARY_SMALLER);

    PUSH(code, POP_JUMP_IF_FALSE);
    PUSH(code, loop_end);

    PUSH(code, LOAD_GLOBAL);
    PUSH(code, __iter__a);

    PUSH(code, LOAD_GLOBAL);
    PUSH(code, __i__a);

    PUSH(code, LOAD_ITEM);

    PUSH(code, STORE_GLOBAL);
    PUSH(code, iden);

    INSERT(code, for_body);

    PUSH(code, LOAD_GLOBAL);
    PUSH(code, __i__a);

    PUSH(code, PUSH_FLOAT);
    PUSH(code, '\x00');
    PUSH(code, '\x00');
    PUSH(code, '\x80');
    PUSH(code, '\x3F');

    PUSH(code, BINARY_ADD);

    PUSH(code, STORE_GLOBAL);
    PUSH(code, __i__a);

    PUSH(code, JUMP_TO);
    PUSH(code, loop_start);

    PUSH(code, ADD_LABEL);
    PUSH(code, loop_end);

    return code;
}
