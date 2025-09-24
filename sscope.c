#include "sscope.h"

struct Scope
new_scope(void) {
    struct Scope scope;
    scope.name = NULL;
    scope.address = 0;
    scope.args_size = 0;
    scope.func_name = NULL;
    scope.func_tag = 0;
    return scope;
}

struct Scompiler* Scompiler_set_frame(struct Scompiler* compiler, struct Sframe* frame) {
    compiler->frame = frame;
    return compiler;
}

struct Scompiler*
Scompiler_new(void) {
    struct Scompiler *compiler = malloc(sizeof(struct Scompiler));
    
    compiler->scope_index = 0;
    compiler->scope_size = 1024;
    
    compiler->local_index = 0;
    compiler->local_size = 1024;

    compiler->loop_index = 0;

    compiler->address = ADDRESS_START;

    compiler->is_in_block = 0;
    compiler->is_in_class = 0;
    compiler->is_in_func = 0;
    compiler->is_in_loop = 0;

    compiler->function_name = malloc(sizeof(char) * 1024);

    compiler->label = 0;
    
    return compiler;
}

struct Scope
creat_scope(char *name, int address, int args_size, int func_tag, char *func_name) {
    struct Scope scope;
    scope.name = name;
    scope.address = address;
    scope.args_size = args_size;
    scope.func_tag = func_tag;
    scope.func_name = func_name;
    return scope;
}

struct Scompiler*
Scompile_add_loop(struct Scompiler *compiler, int continue_label, int break_label) {
    struct loop_stack loop = {continue_label, break_label};

    compiler->loop_stack[compiler->loop_index++] = loop;
    return compiler;
}

struct loop_stack
Scompile_get_loop(struct Scompiler *compiler) {
    return compiler->loop_stack[compiler->loop_index - 1];
}

struct loop_stack
Scompile_pop_loop(struct Scompiler *compiler) {
    struct loop_stack empty_loop = {0, 0};
    struct loop_stack loop = compiler->loop_stack[compiler->loop_index - 1];
    compiler->loop_stack[--compiler->loop_index] = empty_loop;
    return loop;
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

int
remove_scope_address(struct Scompiler *compiler, int address) {
    for (int i = 0; i < compiler->scope_index; i++) {
        struct Scope scope = compiler->scope[i];
        if (scope.address == address) {
            scope.name = NULL;
            scope.address = 0;
            return 0;
        }
    }
    return NOT_FOUND;
}

struct Scompiler*
Scompiler_reset(struct Scompiler *compiler) {
    compiler->scope_index = 0;
    return compiler;
}

int
add_scope_local
(struct Scompiler *compiler, char *name, int address, int args_size) {
    struct Scope scope = new_scope();

    for (int i = 0; i < compiler->local_index; i++) {
        if (strcmp(compiler->local[i].name, name) == 0) {
            return compiler->local[i].address;
        }
    }

    scope.name = name;
    scope.address = address;
    scope.args_size = args_size;
    
    compiler->local[compiler->local_index++] = scope;
    return address;
}

int
find_scope_local
(struct Scompiler *compiler, char *name) {
    for (int i = 0; i < compiler->local_index; i++) {
        struct Scope scope = compiler->local[i];
        if (strcmp(scope.name, name) == 0) {
            return scope.address;
        }
    }
    return NOT_FOUND;
}

struct Scope
find_scope_obj_local
(struct Scompiler *compiler, char *name) {
    for (int i = 0; i < compiler->local_index; i++) {
        struct Scope scope = compiler->local[i];
        if (strcmp(scope.name, name) == 0) {
            return scope;
        }
    }
    
    return new_scope();
}

int
remove_scope_local
(struct Scompiler *compiler, char *name) {
    for (int i = 0; i < compiler->local_index; i++) {
        struct Scope scope = compiler->local[i];
        if (strcmp(scope.name, name) == 0) {
            scope.name = NULL;
            scope.address = 0;
            return 0;
        }
    }
    
    return NOT_FOUND;
}

int
remove_scope_local_address
(struct Scompiler *compiler, int address) {
    for (int i = 0; i < compiler->local_index; i++) {
        struct Scope scope = compiler->local[i];
        if (scope.address == address) {
            scope.name = NULL;
            scope.address = 9999;
            return 0;
        }
    }
    
    return NOT_FOUND;
}

int SunyScopeInitializeCompiler(struct Scompiler *compiler) {
    add_scope(compiler, "print", 10, 1);
    add_scope(compiler, "exit", 11, 1);
    add_scope(compiler, "call", 12, 3);
    add_scope(compiler, "push", 13, 2);
    add_scope(compiler, "pop", 14, 1);
    add_scope(compiler, "size", 15, 1);
    add_scope(compiler, "range", 17, 2);
    add_scope(compiler, "read", 18, 1);
    add_scope(compiler, "puts", 19, 1);
    add_scope(compiler, "number", 20, 1);
    add_scope(compiler, "isdigit", 21, 1);
    return 0;
}

int
add_scope_obj
(struct Scompiler *compiler, struct Scope scope) {
    for (int i = 0; i < compiler->scope_index; i++) {
        if (strcmp(compiler->scope[i].name, scope.name) == 0) {
            return compiler->scope[i].address;
        }
    }
    compiler->scope[compiler->scope_index++] = scope;
    return scope.address;
}

int 
remove_all_local_scope
(struct Scompiler *compiler) {
    for (int i = 0; i < compiler->local_index; i++) {
        struct Scope scope = compiler->local[i];
        scope.name = NULL;
        scope.address = 999;
    }
    compiler->local_index = 0;
    return 0;
}