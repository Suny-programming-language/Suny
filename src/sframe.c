#include "sframe.h"

struct Sframe *
sframe_new
(void) {
    struct Sframe *frame = calloc(1, sizeof(struct Sframe));

    frame->f_back = NULL;
    
    frame->f_code = NULL;

    frame->f_globals_top = NULL;
    frame->f_locals_top = NULL;

    frame->f_globals_size = 0;
    frame->f_locals_size = 0;

    frame->f_globals_index = 0;
    frame->f_locals_index = 0;

    frame->f_stack_index = 0;
    frame->f_stack_size = 0;

    frame->f_code_index = 0;

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

struct Sobj *
Sframe_push
(struct Sframe *frame, struct Sobj *obj) {
    if (frame->f_stack_index >= MAX_FRAME_SIZE) {
        printf("Error: stack overflow\n");
        return NULL;
    };

    frame->f_stack[frame->f_stack_index++] = obj;
    frame->f_stack_size++;

    return obj;
}

struct Sobj *
Sframe_pop
(struct Sframe *frame) {
    if (frame->f_stack_index <= 0) {
        printf("Error: stack underflow\n");
        return NULL;
    };

    struct Sobj *obj = frame->f_stack[--frame->f_stack_index];

    frame->f_stack_size--;

    return obj;
}

int
Sframe_store_global
(struct Sframe *frame, int address, struct Sobj *obj) {
    struct Sobj *global = Sobj_new();
    
    global->type = GLOBAL_OBJ;
    global->f_value = obj;
    global->address = address;

    frame->f_globals[frame->f_globals_index++] = global;
    frame->f_globals_size++;

    return 0;
}

struct Sobj *
Sframe_load_global
(struct Sframe *frame, int address) {
    struct Sobj *load = NULL;

    int found = 0;

    for (int i = 0; i < frame->f_globals_size; i++) {
        if (frame->f_globals[i]->address == address) {
            load = frame->f_globals[i];
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Error: global not found\n");
        return NULL;
    }

    return load;
}

int
Sframe_store_local
(struct Sframe *frame, int address, struct Sobj *obj) {
    struct Sobj *local = Sobj_new();

    local->type = LOCAL_OBJ;
    local->f_value = obj;
    local->address = address;

    frame->f_locals[frame->f_locals_index++] = local;
    frame->f_locals_size++;

    return 0;
}

struct Sobj *
Sframe_load_local
(struct Sframe *frame, int address) {
    struct Sobj *load = NULL;
    
    for (int i = 0; i < frame->f_locals_size; i++) {
        if (frame->f_locals[i]->address == address) {
            load = frame->f_locals[i];
            break;
        }
    }

    return load;
}