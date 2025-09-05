#include "sframe.h"

struct Sframe *
Sframe_new(void) {
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
    frame->f_stack_size = MAX_FRAME_SIZE;

    frame->f_const_index = 0;
    frame->f_const_size = MAX_FRAME_SIZE;

    frame->f_stack = calloc(frame->f_stack_size, sizeof(struct Sobj *));

    frame->f_const = calloc(frame->f_const_size, sizeof(struct Sobj *));

    frame->f_locals = calloc(MAX_FRAME_SIZE, sizeof(struct Sobj *));
    frame->f_globals = calloc(MAX_FRAME_SIZE, sizeof(struct Sobj *));

    frame->f_code_index = 0;

    frame->f_label_map = Slabel_map_new();

    frame->gc_pool = Sgc_new_pool();

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
    frame->f_code_index = 0;
    frame->f_label_map = Slabel_map_set_program(code);
    return frame;
}

struct Sobj *
Sframe_push(struct Sframe *frame, struct Sobj *obj) {
#ifdef DEBUG
    printf("[frame.c] Sframe_push (building...)\n");
#endif

    if (frame->f_stack_index >= frame->f_stack_size) {
        int new_size = frame->f_stack_size * 2;
        struct Sobj **new_stack = realloc(frame->f_stack, new_size * sizeof(struct Sobj *));
        if (!new_stack) {
            printf("Error: realloc failed in Sframe_push\n");
            SUNY_BREAK_POINT;
            return NULL;
        }
        frame->f_stack = new_stack;
        frame->f_stack_size = new_size;
    }

    Sgc_inc_ref(obj);

    frame->f_stack[frame->f_stack_index++] = obj;

#ifdef DEBUG
    printf("[frame.c] Sframe_push (done) stack_index=%d stack_size=%d\n",
           frame->f_stack_index, frame->f_stack_size);
#endif
    return obj;
}

struct Sobj *
Sframe_pop
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[frame.c] struct Sobj *Sframe_pop(struct Sframe *frame) (building...)\n");
#endif
    if (frame->f_stack_index <= 0) {
        printf("Error frame.c: stack underflow stack index: %d\n", frame->f_stack_index);
        SUNY_BREAK_POINT;
        return NULL;
    };

    struct Sobj *obj = frame->f_stack[--frame->f_stack_index];

    dec_ref(obj);

#ifdef DEBUG
    printf("[frame.c] struct Sobj *Sframe_pop(struct Sframe *frame) (done)\n");
#endif
    return obj;
}

struct Sobj *
Sframe_back
(struct Sframe *frame) {
#ifdef DEBUG
printf("[frame.c] struct Sobj *Sframe_back(struct Sframe *frame) (building...)\n");
#endif

#ifdef DEBUG
printf("[frame.c] struct Sobj *Sframe_back(struct Sframe *frame) (done)\n");
#endif

    return frame->f_stack[frame->f_stack_index - 1];
}

int
Sframe_store_global
(struct Sframe *frame, int address, struct Sobj *obj, enum Sobj_t type) {
    
    inc_ref(obj);

    for (int i = 0; i < frame->f_globals_size; i++) {
        if (frame->f_globals[i]->address == address) {
            struct Sobj *old = frame->f_globals[i]->f_value;

            dec_ref(old);
            Sgc_dec_ref(old, frame->gc_pool);

            frame->f_globals[i]->f_value = obj;
            frame->f_globals[i]->type = type;
            frame->f_globals[i]->address = address;

            return 0;
        }
    }

    struct Sobj *global = Sobj_new();

    global->type = type;
    global->f_value = obj;
    global->f_value->address = address;
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
        printf("Error frame.c: global not found address: %d\n", address);
        SUNY_BREAK_POINT;
        return NULL;
    }

    return load;
}

int
Sframe_store_local
(struct Sframe *frame, int address, struct Sobj *obj, enum Sobj_t type) {
#ifdef DEBUG
    printf("[frame.c] int Sframe_store_local(struct Sframe *frame, int address, struct Sobj *obj, enum Sobj_t type) (building...)\n");
#endif
    for (int i = 0; i < frame->f_locals_size; i++) {
        if (frame->f_locals[i]->address == address) {
            struct Sobj *old = frame->f_locals[i]->f_value;

            dec_ref(old);
            Sgc_dec_ref(old, frame->gc_pool);

            frame->f_locals[i]->f_value = obj;
            frame->f_locals[i]->type = type;
            frame->f_locals[i]->address = address;
            return 0;
        }
    }

    struct Sobj *local = Sobj_new();

    local->type = LOCAL_OBJ;
    local->f_value = obj;
    local->f_value->address = address;
    local->address = address;


    frame->f_locals[frame->f_locals_index++] = local;
    frame->f_locals_size++;

#ifdef DEBUG
    printf("[frame.c] int Sframe_store_local(struct Sframe *frame, int address, struct Sobj *obj, enum Sobj_t type) (done)\n");
#endif

    return 0;
}

struct Sobj *
Sframe_load_local
(struct Sframe *frame, int address) {
#ifdef DEBUG
    printf("[frame.c] struct Sobj *Sframe_load_local(struct Sframe *frame, int address) (building...)\n");
#endif

    struct Sobj *load = NULL;
    
    for (int i = 0; i < frame->f_locals_size; i++) {
        if (frame->f_locals[i]->address == address) {
            load = frame->f_locals[i];
            break;
        }
    }

    if (!load) {
        for (int i = 0; i < frame->f_globals_size; i++) {
            if (frame->f_globals[i]->address == address) {
                load = frame->f_globals[i];
                break;
            }
        }

        if (!load) {
            printf("Error frame.c: local not found address: %d\n", address);
            SUNY_BREAK_POINT;
            return NULL;
        }
    }

#ifdef DEBUG
    printf("[frame.c] struct Sobj *Sframe_load_local(struct Sframe *frame, int address) (done)\n");
#endif

    return load;
}

struct Sframe *
Sframe_insert_global
(struct Sframe *frame, struct Sobj **f_global, int size) {
    for (int i = 0; i < size; i++) {
        if (Sframe_already_defined(frame, f_global[i]->address)) {
            printf("Error frame.c: global already defined\n");
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
            printf("Error frame.c: local already defined\n");
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
(struct Sframe *frame, void* func, int address, char* name, int args_size) {
    struct Sc_api_func* api_func = Sc_api_func_set(func, name, address, args_size);

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
    SUNY_BREAK_POINT;   
    return NULL;
}

int
Sframe_store_const
(struct Sframe *frame, struct Sobj *obj) {
    if (frame->f_const_index >= frame->f_const_size) {
        frame->f_const_size *= 2;
        frame->f_const = realloc(frame->f_const, frame->f_const_size * sizeof(struct Sobj *));
    }

    frame->f_const[frame->f_const_index++] = obj;
}

struct Sobj *
Sframe_load_const
(struct Sframe *frame, int address) {
    for (int i = 0; i < frame->f_const_size; i++) {
        if (frame->f_const[i]->address == address) {
            return frame->f_const[i];
        }
    }

    printf("Error frame.c: const not found address: %d\n", address);
    SUNY_BREAK_POINT;
    return NULL;
}