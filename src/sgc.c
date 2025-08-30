#include "sgc.h"

struct Sgarbarge_obj* Sgc_new(void) {
    struct Sgarbarge_obj* obj = malloc(sizeof(struct Sgarbarge_obj));
    obj->next = NULL;
    obj->obj = NULL;
    obj->ref_count = 0;
}

struct Sgarbarge_obj* Sgc_new_obj(struct Sobj* obj) {
    struct Sgarbarge_obj* garbage_obj = Sgc_new();
    garbage_obj->obj = obj;
    return garbage_obj;
}

int ref_count_inc(struct Sobj* obj) {
    obj->gc->ref_count++;
    return 0;
}

int ref_count_dec(struct Sobj* obj) {
    obj->gc->ref_count--;
    return 0;
}