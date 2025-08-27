#include "sscope.h"

struct Scope
new_scope(void) {
    struct Scope scope;
    scope.name = NULL;
    scope.address = 0;
    return scope;
}

int
add_scope(struct Scompiler *compiler, char *name, int address) {
    struct Scope scope = new_scope();
    scope.name = name;
    scope.address = address;
    compiler->scope[compiler->scope_index++] = scope;
    return 0;
}

int
find_scope(struct Scompiler *compiler, char *name) {
    for (int i = 0; i < compiler->scope_index; i++) {
        struct Scope scope = compiler->scope[i];
        if (strcmp(scope.name, name) == 0) {
            return scope.address;
        }
    }
    return 1;
}

int
remove_scope(struct Scompiler *compiler, char *name) {
    for (int i = 0; i < compiler->scope_index; i++) {
        struct Scope scope = compiler->scope[i];
        if (strcmp(scope.name, name) == 0) {
            compiler->scope[i] = compiler->scope[compiler->scope_index - 1];
            compiler->scope_index -= 1;
            return 0;
        }
    }
    return 1;
}