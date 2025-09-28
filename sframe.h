#ifndef SFRAME_H
#define SFRAME_H

#include "sbuiltin.h"
#include "slabel.h"
#include "sbool.h"
#include "sgc.h"

#define POP_OBJ() Sframe_pop(frame)

#define PUSH_OBJ(obj) Sframe_push(frame, obj)

enum Sobj_t;

struct Sframe {
    int f_locals_size;
    int f_globals_size;

    int f_locals_index;
    int f_globals_index;

    int f_stack_index;
    int f_stack_size;

    int f_const_size;
    int f_const_index;

    int f_code_index;

    struct Sobj *f_func;

    struct Sobj **dll_args;
    int dll_args_size;
    int dll_args_index;

    struct Slabel_map *f_label_map;

    struct Sast *f_ast; // for debugging

    struct Sframe *f_back;
    struct Scode *f_code;

    struct Sobj **f_locals;
    struct Sobj **f_globals;
    
    struct Sobj **f_const;

    struct Sobj **f_stack;

    struct Sobj *f_locals_top;
    struct Sobj *f_globals_top;

    struct Garbage_pool *gc_pool;
    
    struct Scompiler *compiler;
};

struct Sframe *
Sframe_new
(void);

int
Sframe_already_defined
(struct Sframe *frame, int address);

struct Sframe *
Sframe_insert_global
(struct Sframe *frame, struct Sobj **f_global, int size);

struct Sframe *
Sframe_insert_local
(struct Sframe *frame, struct Sobj **f_local, int size);

int
Sframe_free
(struct Sframe *frame);

struct Sframe *
Sframe_init
(struct Sframe *frame, struct Scode *code);

struct Sobj *
Sframe_push
(struct Sframe *frame, struct Sobj *obj);

struct Sobj *
Sframe_pop
(struct Sframe *frame);

struct Sobj *
Sframe_back
(struct Sframe *frame);

int
Sframe_store_global
(struct Sframe *frame, int address, struct Sobj *obj, enum Sobj_t type);

struct Sobj *
Sframe_load_global
(struct Sframe *frame, int address);

int
Sframe_store_const
(struct Sframe *frame, struct Sobj *obj);

struct Sobj *
Sframe_load_const
(struct Sframe *frame, int address);

int
Sframe_store_local
(struct Sframe *frame, int address, struct Sobj *obj, enum Sobj_t type);

struct Sobj *
Sframe_load_local
(struct Sframe *frame, int address);

struct Sobj *
Sframe_load_c_api_func
(struct Sframe *frame, void* func, int address, char* name, int args_size);

void*
Sframe_find_c_api_func
(struct Sframe *frame, int address);

struct Sframe*
Sframe_push_number(struct Sframe* frame, float number);

struct Sframe*
Sframe_push_string(struct Sframe* frame, char* string, int size);

struct Sframe*
Sframe_push_bool(struct Sframe* frame, int b);

struct Sobj*
Sframe_get_top(struct Sframe* frame);

struct Sobj*
Sframe_true_pop(struct Sframe* frame);

struct Sframe*
Sframe_call_c_api_func(struct Sframe* frame, void* func);

struct Sframe*
Sframe_call_func_from_dll(struct Sframe* frame, char* dll_name, char* func_name, struct Sobj* args);

#endif // SFRAME_H