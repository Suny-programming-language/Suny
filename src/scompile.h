#ifndef SCOMPILE_H
#define SCOMPILE_H

#include "scode.h"
#include "suny.h"
#include "sparser.h"
#include "sobj.h"

struct Scope {
    char *name;
    int address;
};

struct Scompiler {
    struct Scope scope[1024];
    
    int scope_index;
    int scope_size;
    int address;
};

struct Scope
new_scope(void);

struct Scompiler*
Scompiler_new(void);

struct Scode*
Scompile
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_program
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_binary_expression
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_identifier
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_literal
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_assignment
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_print
(struct Sast *ast, struct Scompiler *compiler);

#endif // SCOMPILE_H