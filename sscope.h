#ifndef SSCOPE_H
#define SSCOPE_H

#include <stdlib.h>
#include <string.h>

#include "sframe.h"

#define ALREADY_DEFINED 999

#define NOT_FOUND 998

#define ADDRESS_START 127

#define SELF_ADDRESS 126

#define creat_label(compiler) (++compiler->label)

#define compiler_set_func(c, f) ((c)->function_name = f)

struct loop_stack {
    int continue_label;
    int break_label;
};

struct Scope {
    char *name;
    int address;
    int args_size;
    int func_tag; // if this global is in a function
    char* func_name; // same but its its function 
};

struct Scompiler {
    struct Scope scope[1024];
    struct Scope local[1024];

    struct loop_stack loop_stack[1024];
    
    int scope_index;
    int scope_size;

    int local_index;
    int local_size;

    int loop_index;

    int address;

    int is_in_func;
    int is_in_block;
    int is_in_class;
    int is_in_loop;

    char* function_name;

    int label;

    struct Sframe* frame;
};

struct Sframe;

struct Scompiler* Scompiler_set_frame(struct Scompiler* compiler, struct Sframe* frame);

struct Scope
creat_scope
(char *name, int address, int args_size, int func_tag, char *func_name);

int 
remove_all_local_scope
(struct Scompiler *compiler);

struct Scompiler*
Scompile_add_loop(struct Scompiler *compiler, int continue_label, int break_label);

struct loop_stack
Scompile_pop_loop(struct Scompiler *compiler);

struct loop_stack
Scompile_get_loop(struct Scompiler *compiler);

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

int
remove_scope_address(struct Scompiler *compiler, int address);

struct Scompiler*
Scompiler_new(void);

struct Scompiler*
Scompiler_reset(struct Scompiler *compiler);

int
add_scope_local
(struct Scompiler *compiler, char *name, int address, int args_size);

int
remove_scope_local_address
(struct Scompiler *compiler, int address);

int
find_scope_local
(struct Scompiler *compiler, char *name);

struct Scope
find_scope_obj_local
(struct Scompiler *compiler, char *name);

int
remove_scope_local
(struct Scompiler *compiler, char *name);

int 
SunyScopeInitializeCompiler
(struct Scompiler *compiler);

#endif