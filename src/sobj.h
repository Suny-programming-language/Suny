#ifndef SOBJ_H
#define SOBJ_H

#include "score.h"
#include "stype.h"
#include "sstr.h"

struct Sgarbarge_obj;
struct Garbage_pool;

#define GC_HEAD struct Sgarbarge_obj* gc

#define MAX_FRAME_SIZE 1024

typedef unsigned char byte_t;
typedef int address_t;

#define Sobj_get_value(obj) ((obj)->value->value)

#define Addressof(obj) ((obj)->address)

#define Sizeof(obj) ((obj)->size)

#define Typeof(obj) ((obj)->type)

#ifndef SOBJ_T
#define SOBJ_T
enum Sobj_t {
    NUMBER_OBJ,
    GLOBAL_OBJ,
    BUILTIN_OBJ,
    LOCAL_OBJ,
    STRING_OBJ,
    LIST_OBJ,
    TRUE_OBJ,
    FALSE_OBJ,
    FUNC_OBJ,
    NULL_OBJ,
};
#endif

struct Svalue {
    float value;
};

struct Sobj {
    GC_HEAD;

    enum Sobj_t type;
    struct Svalue* value;
    
    int address;
    int size;

    struct Sobj *next;
    struct Sobj *prev;

    struct Sobj *f_value; // variable value
    
    struct Stype *f_type; // real value

    struct Sc_api_func* c_api_func;
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