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

SUNY_API struct Sobj *Sisdigit_builtin(struct Sframe *frame) {
    struct Sobj *obj = Sframe_pop(frame);

    char* str = obj->f_type->f_str->string;

    if (Sisstrdigit(str)) {
        struct Sobj *result = Sobj_set_int(1);
        return result;
    } else {
        struct Sobj *result = Sobj_set_int(0);
        return result;
    }

    return NULL;
}

SUNY_API struct Sobj* Snumber(struct Sframe* frame) {
    struct Sobj *string = Sframe_pop(frame);

    float value = Satof(string->f_type->f_str->string);

    struct Sobj *obj = Sobj_set_int(value);

    return obj;
}

SUNY_API struct Sobj* Sputs(struct Sframe* frame) {
    struct Sobj *obj = Sframe_pop(frame);

    Sio_write(obj);

    return Sobj_set_int(0);
}

SUNY_API struct Sobj* Sprintf(struct Sframe* frame) {
    struct Sobj *obj = Sframe_pop(frame);

    Sio_write(obj);

    printf("\n");

    return Sobj_set_int(0);
}

SUNY_API struct Sobj* Sread(struct Sframe* frame) {
    struct Sobj *obj = Sframe_pop(frame);
    char buffer[1024];

    if (obj) {
        Sio_write(obj);
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        struct Sobj *empty = Sobj_make_str("", 0);
        return empty;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    struct Sobj *result = Sobj_make_str(buffer, len);

    return result;
}


SUNY_API struct Sobj* Sexit(struct Sframe* frame) {
    struct Sobj *obj = Sframe_pop(frame);

    exit(obj->value->value);

    return Sobj_set_int(0);
}

SUNY_API struct Sobj *Sload_dll(struct Sframe *frame) {
    struct Sobj *func = Sframe_pop(frame);
    struct Sobj *dll = Sframe_pop(frame);
    struct Sobj *args = Sframe_pop(frame);

    char* dll_name = dll->f_type->f_str->string;
    char* func_name = func->f_type->f_str->string;

    Sdll_func dll_func = dll_get_func(func_name, dll_name);

    builtin_func f = (builtin_func) dll_func;

    for (int i = 0; i < args->f_type->f_list->count; i++) {
        struct Sobj *arg = Slist_get(args->f_type->f_list, i);
        Sframe_push(frame, arg);
    }

    struct Sobj *result = f(frame);

    return result;
}

SUNY_API struct Sobj* Ssize(struct Sframe* frame) {
    struct Sobj *obj = Sframe_pop(frame);

    if (obj->type == LIST_OBJ) {
        return Sobj_set_int(obj->f_type->f_list->count);
    } else if (obj->type == STRING_OBJ) {
        return Sobj_set_int(obj->f_type->f_str->size);
    } else {
        return Sobj_set_int(0);
    }

    return NULL;
}

SUNY_API struct Sobj* Spush(struct Sframe* frame) {
    struct Sobj *list = Sframe_pop(frame);
    struct Sobj *value = Sframe_pop(frame);

    Slist_add(list->f_type->f_list, value);

    struct Sobj *obj = Sobj_set_int(0);

    return list;
}

SUNY_API struct Sobj* Spop(struct Sframe* frame) {
    struct Sobj *obj = Sframe_pop(frame);

    Slist_pop(obj->f_type->f_list);

    struct Sobj *result = Sobj_set_int(0);

    return obj;
}

SUNY_API struct Sobj *Srange(struct Sframe *frame) {
    struct Sobj *end = Sframe_pop(frame);
    struct Sobj *start = Sframe_pop(frame);

    int start_value = start->value->value;
    int end_value = end->value->value;

    struct Slist *list = Slist_range(start_value, end_value);
    struct Sobj *obj = Sobj_make_list(list);

    return obj;
}