#include "sscope.h"

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
    
    compiler->local_index = 0;
    compiler->local_size = 1024;

    compiler->loop_index = 0;

    compiler->address = ADDRESS_START;

    compiler->is_in_block = 0;
    compiler->is_in_class = 0;
    compiler->is_in_func = 0;
    compiler->is_in_loop = 0;


    compiler->label = 0;
    
    return compiler;
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