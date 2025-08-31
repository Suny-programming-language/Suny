#include "seval.h"

struct Sobj *
Seval_add
(struct Sobj *obj1, struct Sobj *obj2) {
#ifdef DEBUG
    printf("[seval.c] struct Sobj *Seval_add(struct Sobj *obj1, struct Sobj *obj2) (pass)\n");
#endif
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        struct Sstr *str = Sstr_add(str1, str2);

        struct Sobj *sobj = Sobj_make_str_obj(str);
        
        return sobj;
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
#ifdef DEBUG
    printf("[seval.c] struct Sobj *Seval_mul(struct Sobj *obj1, struct Sobj *obj2) (pass)\n");
#endif
    if (obj1->type == STRING_OBJ) {
        struct Sstr *str = obj1->f_type->f_str;
        struct Sstr *sstr = Sstr_mul(str, obj2->value->value);

        struct Sobj *sobj = Sobj_make_str_obj(sstr);
        
        return sobj;
    } else if (obj2->type == STRING_OBJ) {
        struct Sstr *str = obj2->f_type->f_str;
        struct Sstr *sstr = Sstr_mul(str, obj1->value->value);

        struct Sobj *sobj = Sobj_make_str_obj(sstr);
        
        return sobj;
    } else {
        return Sobj_set_int(obj1->value->value * obj2->value->value);
    }
}

struct Sobj *
Seval_div
(struct Sobj *obj1, struct Sobj *obj2) {
#ifdef DEBUG
    printf("[seval.c] struct Sobj *Seval_div(struct Sobj *obj1, struct Sobj *obj2) (pass)\n");
#endif
    return Sobj_set_int(obj1->value->value / obj2->value->value);
}

struct Sobj *
Seval_bigger
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        char* a = str1->string;
        char* b = str2->string;

        int size_a = str1->size;
        int size_b = str2->size;

        int result = Scharcmp_bigger(a, b, size_a, size_b);

        return Sobj_set_int(result);
    } else {
        return Sobj_set_int(obj1->value->value > obj2->value->value);
    }
}

struct Sobj *
Seval_smaller
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        char* a = str1->string;
        char* b = str2->string;

        int size_a = str1->size;
        int size_b = str2->size;

        int result = Scharcmp_smaller(a, b, size_a, size_b);

        return Sobj_set_int(result);
    } else {
        return Sobj_set_int(obj1->value->value < obj2->value->value);
    }
}

struct Sobj *
Seval_equal
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        char* a = str1->string;
        char* b = str2->string;

        int size_a = str1->size;
        int size_b = str2->size;

        int result = Scharcmp_equal(a, b, size_a, size_b);

        return Sobj_set_int(result);
    } else {
        return Sobj_set_int(obj1->value->value == obj2->value->value);
    }
}

struct Sobj *
Seval_not_equal
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        char* a = str1->string;
        char* b = str2->string;

        int size_a = str1->size;
        int size_b = str2->size;

        int result = Scharcmp_equal(a, b, size_a, size_b);

        return Sobj_set_int(!result);
    } else {
        return Sobj_set_int(obj1->value->value != obj2->value->value);
    }
}

struct Sobj *
Seval_bigger_and_equal
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        char* a = str1->string;
        char* b = str2->string;

        int size_a = str1->size;
        int size_b = str2->size;

        int result = Scharcmp_bigger(a, b, size_a, size_b);
        int result2 = Scharcmp_equal(a, b, size_a, size_b);

        return Sobj_set_int(result || result2);
    } else {
        return Sobj_set_int(obj1->value->value >= obj2->value->value);
    }
}

struct Sobj *
Seval_smaller_and_equal
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        char* a = str1->string;
        char* b = str2->string;

        int size_a = str1->size;
        int size_b = str2->size;

        int result = Scharcmp_smaller(a, b, size_a, size_b);
        int result2 = Scharcmp_equal(a, b, size_a, size_b);

        return Sobj_set_int(result || result2);
    } else {
        return Sobj_set_int(obj1->value->value <= obj2->value->value);
    }
}