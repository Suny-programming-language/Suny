#ifndef SCOMPILE_H
#define SCOMPILE_H

#include "scode.h"
#include "suny.h"
#include "sparser.h"

struct Scope {
    char *name;
    int address;
};

struct Scompiler {
    struct Scope scope[1024];
    
    int scope_index;
    int scope_size;
};

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

#endif // SCOMPILE_H