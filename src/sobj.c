#include "sobj.h"

struct Sobj* 
Sobj_new(void) {
    struct Sobj *obj = malloc(sizeof(struct Sobj));

    return obj;
}

int 
Sobj_free
(struct Sobj* obj) {
    free(obj);
    obj = NULL;
}