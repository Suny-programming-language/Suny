#include "sbuiltin.h"

struct Sc_api_func* 
Sc_api_func_set
(void* func, char* name, int address, int args_size) {
    struct Sc_api_func* api_func = malloc(sizeof(struct Sc_api_func));
    api_func->func = func;
    api_func->name = name;
    api_func->address = address;
    api_func->args_size = args_size;
    return api_func;
}

SUNY_API struct Sobj* Sprintf(struct Sframe* frame) {
    struct Sobj *obj = Sframe_pop(frame);

    Sio_write(obj);

    Sframe_push(frame, Sobj_set_int(0));

    return NULL;
}

SUNY_API struct Sobj* Sexit(struct Sframe* frame) {
    struct Sobj *obj = Sframe_pop(frame);

    exit(obj->value->value);

    Sframe_push(frame, Sobj_set_int(0));

    return NULL;
}

SUNY_API struct Sobj *Sload_dll(struct Sframe *frame) {
    struct Sobj *func = Sframe_pop(frame);
    struct Sobj *dll = Sframe_pop(frame);

    char* dll_name = dll->f_type->f_str->string;
    char* func_name = func->f_type->f_str->string;

    Sdll_func dll_func = dll_get_func(func_name, dll_name);

    builtin_func f = (builtin_func) dll_func;

    struct Sobj *result = f(frame);

    Sframe_push(frame, result);

    return NULL;
}

SUNY_API struct Sobj* Ssize(struct Sframe* frame) {
    struct Sobj *obj = Sframe_pop(frame);

    if (obj->type == LIST_OBJ) {
        Sframe_push(frame, Sobj_set_int(obj->f_type->f_list->count));
    } else if (obj->type == STRING_OBJ) {
        Sframe_push(frame, Sobj_set_int(obj->f_type->f_str->size));
    } else {
        Sframe_push(frame, Sobj_set_int(0));
    }
}

SUNY_API struct Sobj* Spush(struct Sframe* frame) {
    struct Sobj *list = Sframe_pop(frame);
    struct Sobj *value = Sframe_pop(frame);

    Slist_add(list->f_type->f_list, value);

    return list;
}

SUNY_API struct Sobj* Spop(struct Sframe* frame) {
    struct Sobj *obj = Sframe_pop(frame);

    Slist_pop(obj->f_type->f_list);

    return obj;
}