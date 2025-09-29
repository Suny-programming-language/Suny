#include "smeta.h"

struct Smeta* Smeta_new(void) {
    struct Smeta* meta = malloc(sizeof(struct Smeta));
    meta->mm_add = NULL;
    meta->mm_sub = NULL;
    meta->mm_mul = NULL;
    meta->mm_div = NULL;
    meta->mm_tostring = NULL;
    meta->mm_type = NULL;
    meta->mm_eq = NULL;
    meta->mm_ne = NULL;
    meta->mm_gt = NULL;
    meta->mm_ge = NULL;
    meta->mm_lt = NULL;
    meta->mm_le = NULL;
    meta->mm_call = NULL;
    meta->mm_index = NULL;
    meta->mm_free = NULL;
    return meta;
}

void Smeta_set(struct Sobj* obj, const char* name, void* fn) {
    if (!obj->meta) {
        obj->meta = Smeta_new();
    }

    if (strcmp(name, "__add__") == 0) obj->meta->mm_add = fn;
    else if (strcmp(name, "__sub__") == 0) obj->meta->mm_sub = fn;
    else if (strcmp(name, "__mul__") == 0) obj->meta->mm_mul = fn;
    else if (strcmp(name, "__div__") == 0) obj->meta->mm_div = fn;

    else if (strcmp(name, "__tostring__") == 0) obj->meta->mm_tostring = fn;
    else if (strcmp(name, "__type__") == 0) obj->meta->mm_type = fn;

    else if (strcmp(name, "__eq__") == 0) obj->meta->mm_eq = fn;
    else if (strcmp(name, "__ne__") == 0) obj->meta->mm_ne = fn;
    else if (strcmp(name, "__gt__") == 0) obj->meta->mm_gt = fn;
    else if (strcmp(name, "__ge__") == 0) obj->meta->mm_ge = fn;
    else if (strcmp(name, "__lt__") == 0) obj->meta->mm_lt = fn;
    else if (strcmp(name, "__le__") == 0) obj->meta->mm_le = fn;

    else if (strcmp(name, "__call__") == 0) obj->meta->mm_call = fn;
    else if (strcmp(name, "__index__") == 0) obj->meta->mm_index = fn;

    else if (strcmp(name, "__free__") == 0) obj->meta->mm_free = fn;
}

struct Smeta* Sobj_set_meta(struct Sobj* obj, struct Smeta* meta) { obj->meta = meta; return meta; }

void* Sobj_get_metamethod(struct Sobj* obj, const char* name) {
    if (obj->meta && obj->meta->mm_add && strcmp(name, "__add__") == 0) return obj->meta->mm_add;
    if (obj->meta && obj->meta->mm_sub && strcmp(name, "__sub__") == 0) return obj->meta->mm_sub;
    if (obj->meta && obj->meta->mm_mul && strcmp(name, "__mul__") == 0) return obj->meta->mm_mul;
    if (obj->meta && obj->meta->mm_div && strcmp(name, "__div__") == 0) return obj->meta->mm_div;

    if (obj->meta && obj->meta->mm_tostring && strcmp(name, "__tostring__") == 0) return obj->meta->mm_tostring;
    if (obj->meta && obj->meta->mm_type && strcmp(name, "__type__") == 0) return obj->meta->mm_type;

    if (obj->meta && obj->meta->mm_eq && strcmp(name, "__eq__") == 0) return obj->meta->mm_eq;
    if (obj->meta && obj->meta->mm_ne && strcmp(name, "__ne__") == 0) return obj->meta->mm_ne;
    if (obj->meta && obj->meta->mm_gt && strcmp(name, "__gt__") == 0) return obj->meta->mm_gt;
    if (obj->meta && obj->meta->mm_ge && strcmp(name, "__ge__") == 0) return obj->meta->mm_ge;
    if (obj->meta && obj->meta->mm_lt && strcmp(name, "__lt__") == 0) return obj->meta->mm_lt;
    if (obj->meta && obj->meta->mm_le && strcmp(name, "__le__") == 0) return obj->meta->mm_le;

    if (obj->meta && obj->meta->mm_call && strcmp(name, "__call__") == 0) return obj->meta->mm_call;
    if (obj->meta && obj->meta->mm_index && strcmp(name, "__index__") == 0) return obj->meta->mm_index;

    if (obj->meta && obj->meta->mm_free && strcmp(name, "__free__") == 0) return obj->meta->mm_free;

    return NULL;
}