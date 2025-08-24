#ifndef SFRAME_H
#define SFRAME_H

#include "sobj.h"
#include "suny.h"

#define POP_OBJ() Sframe_pop(frame)

#define PUSH_OBJ(obj) Sframe_push(frame, obj)

struct Sframe {
    struct Sframe *f_back;
    struct Scode *f_code;

    struct Sobj *f_locals[MAX_FRAME_SIZE];
    struct Sobj *f_globals[MAX_FRAME_SIZE];

    struct Sobj *f_stack[MAX_FRAME_SIZE];

    struct Sobj *f_locals_top;
    struct Sobj *f_globals_top;

    int f_locals_size;
    int f_globals_size;

    int f_locals_index;
    int f_globals_index;

    int f_stack_index;
    int f_stack_size;

    int f_code_index;
};  

struct Sframe *
sframe_new
(void);

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

int
Sframe_store_global
(struct Sframe *frame, int address, struct Sobj *obj);

struct Sobj *
Sframe_load_global
(struct Sframe *frame, int address);

int
Sframe_store_local
(struct Sframe *frame, int address, struct Sobj *obj);

struct Sobj *
Sframe_load_local
(struct Sframe *frame, int address);

#endif // SFRAME_H