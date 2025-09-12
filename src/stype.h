#ifndef STYPE_H
#define STYPE_H

#include "score.h"
#include "sobj.h"
#include "sframe.h"
#include "scode.h"
#include "max.h"

typedef void (*SunyGcFn)(void* data);
typedef void (*SunyToStringFn)(void* data, char* buf, size_t bufsize);

struct Scall_context;
struct Sfunc;
struct Sstr;
struct Slist;
struct Sbool;
struct Sclass;
struct Stype;
struct Suserdata;

struct Suserdata {
    void* data;
    struct Stype* type;
};

struct Sfunc {
    struct Sfunc *inner;
    
    struct Sobj** inner_funcs;
    int inner_funcs_size;
    int inner_funcs_capacity;

    struct Sframe *frame;
    struct Scode *code;

    int args_index;
    int code_index;

    int args_size;
    int code_size;

    struct Sobj *obj;
    struct Sobj **params;

    struct Scall_context *call_context;
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

struct Sstr {
    unsigned char buff[MAX_IDENTIFIER_SIZE];
    int size;
    char* string;
};

struct Slist {
    struct Sobj *start;
    struct Sobj *end;

    struct Sobj** array;
    
    int count;
    int capacity;
};

struct Sbool {
    int _bool;
};

struct Sclass {
    struct Sobj** methods;
    int count;
    int capacity;
};

struct Stype {

    struct Sfunc *f_func;
    struct Sstr *f_str;
    struct Svalue *f_value;
    struct Sframe *f_frame;
    struct Scode *f_code;
    struct Sclass *f_class;
    struct Sobj *f_obj;
    struct Slist *f_list;
    struct Sbool *f_bool;

    struct Scall_context *f_call_context;

    struct Suserdata *f_userdata;

    SunyGcFn gc;
    SunyToStringFn tostring;

    char* doc; // document of userdata
    char* name; // name of userdata
    
    int f_size;
};

struct Stype *
Stype_new(void);

int 
Stype_free
(struct Stype *type);

#endif // STYPE_H