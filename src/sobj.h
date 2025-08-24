#ifndef SOBJ_H
#define SOBJ_H

#include "suny.h"

#define MAX_FRAME_SIZE 1024

typedef unsigned char byte_t;

enum Sobj_t {
    NUMBER_OBJ,
    GLOBAL_OBJ,
    LOCAL_OBJ,
    NULL_OBJ,
};

struct Svalue {
    float value;
};

struct Sobj {
    enum Sobj_t type;
    struct Svalue* value;
    
    int address;
    int size;

    struct Sobj *next;
    struct Sobj *prev;

    struct Sobj *f_value; // variable value
};

struct Svalue* 
Svalue_new(void);

struct Sobj* 
Sobj_new(void);

int 
Sobj_free
(struct Sobj* obj);

struct Sobj*
Sobj_set_int
(float value);

#endif // SOBJ_H