#ifndef SOBJ_H
#define SOBJ_H

#include "suny.h"

#define MAX_STACK_SIZE 1024

enum Sobj_t {
    NUMBER_OBJ,
    NULL_OBJ,
};

struct Svalue {
    float value;
};

struct Sobj {
    enum Sobj_t type;
    struct Svalue* value;
};

struct Sobj* 
Sobj_new(void);

int 
Sobj_free
(struct Sobj* obj);

#endif // SOBJ_H