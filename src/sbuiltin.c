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

    if (obj->type == STRING_OBJ) {
        printf("%s\n", obj->f_type->f_str->string);
    } else if (obj->type == NUMBER_OBJ) {
        printf("%f\n", obj->value->value);
    }

    return NULL;
}

SUNY_API struct Sobj* Sexit(struct Sframe* frame) {
    struct Sobj *obj = Sframe_pop(frame);

    exit(obj->value->value);

    return NULL;
}