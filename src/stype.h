#ifndef STYPE_H
#define STYPE_H

#include "suny.h"
#include "sobj.h"
#include "sframe.h"
#include "scode.h"

struct Sfunc {
    struct Sfunc *inner;

    struct Sframe *frame;
    struct Scode *code;

    int args_index;
    int code_index;

    int args_size;
    int code_size;

    struct Sobj *obj;
    struct Sobj **params;
};

struct Scall_context {
    struct Sfunc *func;

    struct Sframe *frame;
    struct Sframe *main_frame;
    
    struct Sobj **local_t;

    struct Scode *code;

    int args_index;
    int code_index;
    int stack_index;
    int local_index;

    struct Sobj *obj;
    struct Sobj *ret_obj;
};

struct Stype {
    struct Sobj *f_type;
    struct Sobj *f_value;

    struct Sfunc *f_func;
    struct Scall_context *f_call_context;

    int f_size;
};

struct Stype *
Stype_new(void);

int 
Stype_free
(struct Stype *type);

#endif // STYPE_H