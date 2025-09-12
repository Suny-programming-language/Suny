#ifndef SGC_H
#define SGC_H

#include "score.h"
#include "sobj.h"

struct Sframe;

struct Sgarbarge_obj {
    struct Sobj* obj;
    int ref_count;
    struct Sgarbarge_obj* next;
};

struct Garbage_pool {
    struct Sobj** garbage_pool;
    
    int pool_size;
    int pool_index;

    int is_activate;
};

#define inc_ref(obj) ((obj)->gc->ref_count++)
#define dec_ref(obj) ((obj)->gc->ref_count--)

#define POOL_SIZE_LIMIT 5

struct Sgarbarge_obj* Sgc_new(void);

struct Sgarbarge_obj* Sgc_new_obj(struct Sobj* obj);

struct Garbage_pool* Sgc_new_pool(void);
int Sgc_free_pool(struct Garbage_pool* pool);
struct Garbage_pool* Sgc_push_garbage_obj(struct Garbage_pool* pool, struct Sobj* obj);

void Sgc_collect(struct Garbage_pool* pool);

int Sgc_inc_ref(struct Sobj* obj);
int Sgc_dec_ref(struct Sobj* obj, struct Garbage_pool* pool);

int Sgc_activate(struct Sframe *frame);
int Sgc_deactivate(struct Sframe *frame);

#endif // SGC_H