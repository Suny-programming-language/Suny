#ifndef SOBJ_H
#define SOBJ_H

#include "score.h"
#include "stype.h"
#include "sstr.h"
#include "sfunc.h"
#include "score.h"
#include "smeta.h"
#include "suserdata.h"

struct Sgarbarge_obj;
struct Garbage_pool;
struct Smeta;

#define NULL_CODE_PTR Scode_new()

#define GC_HEAD struct Sgarbarge_obj* gc

#define MAX_FRAME_SIZE 1024

typedef unsigned char byte_t;
typedef int address_t;

#define Sobj_get_value(obj) ((obj)->value->value)

#define Addressof(obj) ((obj)->address)

#define Sizeof(obj) ((obj)->size)

#define Typeof(obj) ((obj)->type)

enum Sobj_t {
    NUMBER_OBJ,
    GLOBAL_OBJ,
    BUILTIN_OBJ,
    LOCAL_OBJ,
    STRING_OBJ,
    LIST_OBJ,
    USER_DATA_OBJ,
    TRUE_OBJ,
    FALSE_OBJ,
    FUNC_OBJ,
    NULL_OBJ,
};

struct Svalue {
    float value;
};

struct Sobj {
    GC_HEAD;

    enum Sobj_t type;
    struct Svalue* value;
    
    int address;
    int size;

    int is_free;

    char* dname; // data name
    char* ddoc; // data document

    struct Sobj *next;
    struct Sobj *prev;

    struct Sobj *f_value; // variable value
    
    struct Stype *f_type; // real value

    struct Sc_api_func* c_api_func;

    struct Smeta* meta; // metatable
};

struct Svalue* 
Svalue_new(void);

struct Sobj* 
Sobj_new(void);

int 
Sobj_free
(struct Sobj* obj);

int
Sobj_free_objs
(struct Sobj** objs, int size);

struct Sobj*
Sobj_set_int
(float value);

#endif // SOBJ_H