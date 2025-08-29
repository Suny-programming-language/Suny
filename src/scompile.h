#ifndef SCOMPILE_H
#define SCOMPILE_H

#include "scode.h"
#include "suny.h"
#include "sparser.h"
#include "sobj.h"
#include "sbuiltin.h"
#include "sscope.h"

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
Scompile_return
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_string
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_if
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_while
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_break
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_continue
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_list
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_extract
(struct Sast *ast, struct Scompiler *compiler);

struct Scode*
Scompile_store_index
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

#endif // SCOMPILE_H