#include "seval.h"

struct Sobj *
Seval_add
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;
        struct Sstr *str = Sstr_add(str1, str2);

        return Sobj_make_str(str->string, str->size);
    } else {
        return Sobj_set_int(obj1->value->value + obj2->value->value);
    }
}

struct Sobj *
Seval_sub
(struct Sobj *obj1, struct Sobj *obj2) {
    return Sobj_set_int(obj1->value->value - obj2->value->value);
}

struct Sobj *
Seval_mul
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ) {
        struct Sstr *str = obj1->f_type->f_str;
        struct Sstr *sstr = Sstr_mul(str, obj2->value->value);
    } else if (obj2->type == STRING_OBJ) {
        struct Sstr *str = obj2->f_type->f_str;
        struct Sstr *sstr = Sstr_mul(str, obj1->value->value);
    } else {
        return Sobj_set_int(obj1->value->value * obj2->value->value);
    }
}

struct Sobj *
Seval_div
(struct Sobj *obj1, struct Sobj *obj2) {
    return Sobj_set_int(obj1->value->value / obj2->value->value);
}