#ifndef SCOMPILE_H
#define SCOMPILE_H

#include "scode.h"
#include "suny.h"
#include "sparser.h"
#include "sobj.h"
#include "sbuiltin.h"

#define ALREADY_DEFINED 999

#define NOT_FOUND 998

#define ADDRESS_START 127

struct Scope {
    char *name;
    int address;
    int args_size;
};

struct Scompiler {
    struct Scope scope[1024];
    
    int scope_index;
    int scope_size;
    int address;

    int is_in_func;
    int is_in_block;
    int is_in_class;
};

struct Scope
new_scope(void);

int
add_scope
(struct Scompiler *compiler, char *name, int address, int args_size);

int
find_scope
(struct Scompiler *compiler, char *name);

struct Scope
find_scope_obj
(struct Scompiler *compiler, char *name);

int
remove_scope
(struct Scompiler *compiler, char *name);

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
Scompile_comparison
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_print
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_function
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_function_call
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_block
(struct Sast **block, struct Scompiler *compiler, 
    int block_size);

struct Scode*
Scompile_body_func
(struct Sast **block, struct Scompiler *compiler, 
    int block_size, 
    char **args, 
    int args_size);

struct Scode*
Scompile_return
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_string
(struct Sast *ast, struct Scompiler *compiler);

#endif // SCOMPILE_H