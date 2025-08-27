#include "sobj.h"

struct Svalue* 
Svalue_new(void) {
    struct Svalue *value = malloc(sizeof(struct Svalue));
    value->value = 0;
    return value;
}

struct Sobj* 
Sobj_new(void) {
    struct Sobj *obj = malloc(sizeof(struct Sobj));

    obj->type = NULL_OBJ;
    obj->value = Svalue_new();
    obj->size = 0;
    obj->address = 0;

    obj->f_value = NULL;
    obj->f_type = NULL;

    return obj;
}

int 
Sobj_free
(struct Sobj* obj) {
    free(obj);
    obj = NULL;
}

struct Sobj*
Sobj_set_int
(float value) {
    struct Sobj *obj = Sobj_new();
    obj->type = NUMBER_OBJ;
    obj->value->value = value;
    return obj;
}