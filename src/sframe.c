#include "sframe.h"

struct Sframe *
Sframe_new
(void) {
    struct Sframe *frame = calloc(1, sizeof(struct Sframe));

    frame->f_back = NULL;
    
    frame->f_code = NULL;

    frame->f_globals_top = NULL;
    frame->f_locals_top = NULL;

    frame->f_stack = calloc(MAX_FRAME_SIZE, sizeof(struct Sobj *));

    frame->f_locals = calloc(MAX_FRAME_SIZE, sizeof(struct Sobj *));
    frame->f_globals = calloc(MAX_FRAME_SIZE, sizeof(struct Sobj *));

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
(struct Sframe *frame, struct Scode *code) {
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
        printf("Error: stack underflow stack index: %d\n", frame->f_stack_index);
        return Sobj_new();
    };

    struct Sobj *obj = frame->f_stack[--frame->f_stack_index];

    frame->f_stack_size--;

    return obj;
}

int
Sframe_store_global
(struct Sframe *frame, int address, struct Sobj *obj, enum Sobj_t type) {
    struct Sobj *global = Sobj_new();
    
    global->type = type;
    global->f_value = obj;
    global->address = address;

    for (int i = 0; i < frame->f_globals_size; i++) {
        if (frame->f_globals[i]->address == address) {
            frame->f_globals[i] = global;
            return 0;
        }
    }

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
(struct Sframe *frame, int address, struct Sobj *obj, enum Sobj_t type) {
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

struct Sframe *
Sframe_insert_global
(struct Sframe *frame, struct Sobj **f_global, int size) {
    for (int i = 0; i < size; i++) {
        if (Sframe_already_defined(frame, f_global[i]->address)) {
            printf("Error: global already defined\n");
            SUNY_BREAK_POINT;
        }
        
        frame->f_globals[frame->f_globals_index++] = f_global[i];
    }

    frame->f_globals_size += size;

    return frame;
}

struct Sframe *
Sframe_insert_local
(struct Sframe *frame, struct Sobj **f_local, int size) {
    for (int i = 0; i < size; i++) {
        if (Sframe_already_defined(frame, f_local[i]->address)) {
            printf("Error: local already defined\n");
            SUNY_BREAK_POINT;
        }

        frame->f_locals[frame->f_locals_index++] = f_local[i];
    }

    frame->f_locals_size += size;

    return frame;
}

int
Sframe_already_defined
(struct Sframe *frame, int address) {
    for (int i = 0; i < frame->f_locals_size; i++) {
        if (frame->f_locals[i]->address == address) {
            return 1;
        }
    }

    return 0;
}

struct Sobj *
Sframe_load_c_api_func
(struct Sframe *frame, void* func, int address, char* name) {
    struct Sc_api_func* api_func = Sc_api_func_set(func, name, address);

    struct Sobj *load = Sobj_new();

    load->type = BUILTIN_OBJ;
    load->address = address;
    load->c_api_func = api_func;

    Sframe_store_global(frame, address, load, BUILTIN_OBJ);

    return load;
}

void*
Sframe_find_c_api_func
(struct Sframe *frame, int address) {
    for (int i = 0; i < frame->f_globals_size; i++) {
        if (frame->f_globals[i]->address == address) {
            return frame->f_globals[i]->c_api_func->func;
        }
    }

    printf("Error: function not found\n");
    return NULL;
} 