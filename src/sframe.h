#ifndef SFRAME_H
#define SFRAME_H

#include "sbuiltin.h"
#include "slabel.h"

#define POP_OBJ() Sframe_pop(frame)

#define PUSH_OBJ(obj) Sframe_push(frame, obj)

#ifndef SOBJ_T
#define SOBJ_T
enum Sobj_t {
    NUMBER_OBJ,
    GLOBAL_OBJ,
    BUILTIN_OBJ,
    LOCAL_OBJ,
    STRING_OBJ,
    LIST_OBJ,
    TRUE_OBJ,
    FALSE_OBJ,
    FUNC_OBJ,
    NULL_OBJ,
};
#endif

struct Sframe {
    int f_locals_size;
    int f_globals_size;

    int f_locals_index;
    int f_globals_index;

    int f_stack_index;
    int f_stack_size;

    int f_code_index;

    struct Sobj *f_func;

    struct Slabel_map *f_label_map;

    struct Sast *f_ast; // for debugging

    struct Sframe *f_back;
    struct Scode *f_code;

    struct Sobj **f_locals;
    struct Sobj **f_globals;

    struct Sobj **f_stack;

    struct Sobj *f_locals_top;
    struct Sobj *f_globals_top;
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

#endif // SFRAME_H