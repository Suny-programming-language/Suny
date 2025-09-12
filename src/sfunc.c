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
    
    func->code = Scode_new();
    func->frame = Sframe_new();

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

    Scode_free(func->code);
    Sframe_free(func->frame);
    free(func->params);

    if (func->call_context) {
        Scall_context_free(func->call_context);
    }

    free(func);

#ifdef DEBUG
    printf("[sfunc.c] int Sfunc_free(struct Sfunc *func) (done)\n");
#endif

    return 0;
}

struct Sfunc *
Sfunc_ready
(struct Sfunc *func, int args_size) {
    int address = 0;

    for (int i = 0; i < args_size; i++) {
        struct Sobj *arg = Sobj_new();
        arg->address = address++;
        arg->type = LOCAL_OBJ;
        func->params[i] = arg;
    }

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

    context->func = Sfunc_obj_new();
    context->code = Scode_new();
    context->frame = Sframe_new();

    context->main_frame = Sframe_new();

    context->args_index = 0;
    context->code_index = 0;
    context->local_index = 0;
    context->stack_index = 0;

    context->obj = NULL;
    context->local_t = NULL;
    context->ret_obj = Sobj_set_int(0);

    return context;
}

struct Scall_context *
Scall_context_set_func
(struct Scall_context *context, struct Sfunc *func) {
    context->func = func;
    context->code = func->code;
    context->obj = func->obj;
    context->local_t = func->frame->f_locals;
    context->local_index = func->frame->f_locals_index;
    context->stack_index = func->frame->f_stack_index;
    context->code_index = func->code_index;
    context->args_index = func->args_index;

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

int 
Scall_context_free
(struct Scall_context *context) {
#ifdef DEBUG
    printf("[sfunc.c] int Scall_context_free(struct Scall_context *context) (building...)\n");
#endif

    free(context);

#ifdef DEBUG
    printf("[sfunc.c] int Scall_context_free(struct Scall_context *context) (done)\n");
#endif
    return 0;
}