#include "smeta.h"

struct Smeta* Smeta_new(void) {
    struct Smeta* meta = malloc(sizeof(struct Smeta));
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
}