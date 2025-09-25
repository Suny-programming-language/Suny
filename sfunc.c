#include "sfunc.h"

struct Sfunc *
Sfunc_obj_new(void) {
    struct Sfunc *func = malloc(sizeof(struct Sfunc));

    func->args_index = 0;
    func->code_index = 0;

    func->inner_funcs = NULL;
    func->inner_funcs_size = 0;
    func->inner_funcs_capacity = 0;

    func->code_size = 0;
    func->args_size = 0;
    
    func->frame = NULL;

    func->inner = NULL;
    func->obj = NULL;

    func->call_context = NULL;

    func->params = calloc(MAX_ARGS_SIZE, sizeof(struct Sobj*));

    return func;
}

int 
Sfunc_free
(struct Sfunc *func) {
    #ifdef DEBUG
    printf("[sfunc.c] int Sfunc_free(struct Sfunc *func) (building...)\n");
    #endif

    if (func->code) {
        Scode_free(func->code);
    }
    
    free(func->params);
    free(func);

#ifdef DEBUG
    printf("[sfunc.c] int Sfunc_free(struct Sfunc *func) (done)\n");
#endif

    return 0;
}

struct Sfunc *
Sfunc_ready
(struct Sfunc *func, int args_size) {
    return func;
}

struct Sfunc *
Sfunc_set
(struct Scode *code, int args_size, int code_size) {
    struct Sfunc *func = Sfunc_obj_new();
    func->code = code;
    func->args_size = args_size;
    func->code_size = code_size;
    return func;
}

struct Scall_context *
Scall_context_new(void) {
    struct Scall_context *context = malloc(sizeof(struct Scall_context));

    context->frame = Sframe_new();

    Sobj_free_objs(context->frame->f_globals, context->frame->f_globals_index);

    context->args_index = 0;
    context->code_index = 0;
    context->local_index = 0;
    context->stack_index = 0;

    context->obj = NULL;
    context->local_t = NULL;
    context->ret_obj = NULL;

    return context;
}

struct Scall_context *
Scall_context_set_func
(struct Scall_context *context, struct Sfunc *func) {
    Sframe_init(context->frame, func->code);

    return context;
}

struct Sfunc*
Sfunc_set_func
(struct Sfunc *func, struct Sframe *frame, struct Scode *code, int args_size) {
    func->frame = frame;
    func->code = code;
    func->args_size = args_size;
    return func;
}

struct Sobj*
Sobj_set_func
(struct Sfunc *func) {
    struct Sobj *obj = Sobj_new();
    obj->f_type = Stype_new();
    obj->type = FUNC_OBJ;
    obj->f_type->f_func = func;
    return obj;
}

// "i have no idea what am i doing" (8:30 9/9/2025)

int Scall_context_free_frame(struct Scall_context *context) {
    struct Sframe *frame = context->frame;

    Sobj_free_objs(frame->f_stack, frame->f_stack_index);
    Slabel_map_free(frame->f_label_map);
    free(frame->f_locals);
    free(frame);

    return 0;   
}

int 
Scall_context_free
(struct Scall_context *context) {
#ifdef DEBUG
    printf("[sfunc.c] int Scall_context_free(struct Scall_context *context) building...)\n");
#endif

    if (context->frame) {
        Scall_context_free_frame(context);
    }

    free(context);

#ifdef DEBUG
    printf("[sfunc.c] int Scall_context_free(struct Scall_context *context) (done)\n");
#endif
    return 0;
}