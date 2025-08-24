#include "sframe.h"

struct Sframe *
sframe_new
(void) {
    struct Sframe *frame = calloc(1, sizeof(struct Sframe));

    frame->f_back = NULL;
    
    frame->f_code = NULL;

    frame->f_globals[0] = Sobj_new();
    frame->f_locals[0] = Sobj_new();
    frame->f_stack[0] = Sobj_new();

    frame->f_globals_top = NULL;
    frame->f_locals_top = NULL;

    frame->f_globals_size = 0;
    frame->f_locals_size = 0;

    frame->f_globals_index = 0;
    frame->f_locals_index = 0;

    frame->f_stack_index = 0;
    frame->f_stack_size = 0;

    return frame;
}

int
Sframe_free
(struct Sframe *frame) {
    free(frame);
    return 0;
}

struct Sframe *
Sframe_init
(struct Scode *code) {
    struct Sframe *frame = sframe_new();
    frame->f_code = code;
    return frame;
}