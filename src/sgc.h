#ifndef SGC_H
#define SGC_H

#include "suny.h"
#include "sobj.h"

struct Sgarbarge_obj {
    struct Sobj* obj;
    int ref_count;
    struct Sgarbarge_obj* next;
};

struct Sgarbarge_obj* Sgc_new(void);

struct Sgarbarge_obj* Sgc_new_obj(struct Sobj* obj);

int ref_count_inc(struct Sobj* obj);
int ref_count_dec(struct Sobj* obj);

#endif // SGC_H