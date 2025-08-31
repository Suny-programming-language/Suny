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

struct Garbage_pool* Sgc_new_pool(void) {
    struct Garbage_pool* pool = malloc(sizeof(struct Garbage_pool));
    pool->pool_size = 1024;
    pool->pool_index = 0;
    pool->is_activate = 0;

    pool->garbage_pool = malloc(sizeof(struct Sobj*) * pool->pool_size);
    return pool;
}

struct Garbage_pool* Sgc_push_garbage_obj(struct Garbage_pool* pool, struct Sobj* obj) {
    if (pool->pool_index >= pool->pool_size) {
        pool->pool_size *= 2;
        pool->garbage_pool = realloc(pool->garbage_pool, pool->pool_size * sizeof(struct Sobj*));
    }

    pool->garbage_pool[pool->pool_index++] = obj;
    return pool;
}

void Sgc_collect(struct Garbage_pool* pool) {
    if (pool->is_activate == 0) {
        printf("Garbage collector is not active\n");
        SUNY_BREAK_POINT;
        return;
    }

    for (int i = 0; i < pool->pool_index; i++) {
        struct Sobj* obj = pool->garbage_pool[i];

        if (obj->gc->ref_count < 1) {
            Sobj_free(obj);
        }

        pool->garbage_pool[i] = NULL;
    }

    pool->pool_index = 0;

    return;
}

int Sgc_inc_ref(struct Sobj* obj) {
    inc_ref(obj);
    return 0;
}

int Sgc_dec_ref(struct Sobj* obj, struct Garbage_pool* pool) {
    if (obj->gc->ref_count < 1) {
        Sgc_push_garbage_obj(pool, obj);
    }
    return 0;
}

int Sgc_activate(struct Sframe *frame) {
    if (frame->gc_pool->is_activate) {
        printf("Garbage collector is already active\n");
        SUNY_BREAK_POINT;
        return 1;
    }

    frame->gc_pool->is_activate = 1;
    return 0;
}

int Sgc_deactivate(struct Sframe *frame) {
    if (!frame->gc_pool->is_activate) {
        printf("Garbage collector is not active\n");
        SUNY_BREAK_POINT;
        return 1;
    }

    frame->gc_pool->is_activate = 0;
    return 0;
}