#ifndef SFRAME_H
#define SFRAME_H

#include "sobj.h"
#include "suny.h"

struct Sframe {
    struct Sframe *f_back;
    struct Scode *f_code;

    struct Sobj *f_locals[MAX_STACK_SIZE];
    struct Sobj *f_globals[MAX_STACK_SIZE];

    struct Sobj *f_stack[MAX_STACK_SIZE];

    struct Sobj *f_locals_top;
    struct Sobj *f_globals_top;

    int f_locals_size;
    int f_globals_size;

    int f_locals_index;
    int f_globals_index;

    int f_stack_index;
    int f_stack_size;
};  

struct Sframe *
sframe_new
(void);

int
Sframe_free
(struct Sframe *frame);

struct Sframe *
Sframe_init
(struct Scode *code);

#endif // SFRAME_H