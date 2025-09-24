#ifndef SFUNC_H
#define SFUNC_H

#include "stype.h"
#include "scode.h"
#include "sframe.h"

#define MAX_ARGS_SIZE 1024

#define Sobj_get_func(obj) ((obj)->f_type->f_func)

struct Sfunc*
Sfunc_obj_new(void);

struct Sfunc *
Sfunc_ready
(struct Sfunc *func, int args_size);

struct Scall_context *
Scall_context_new(void);

struct Scall_context*
Scall_context_set_func
(struct Scall_context *context, struct Sfunc *func);

struct Sfunc*
Sfunc_set_func
(struct Sfunc *func, struct Sframe *frame, struct Scode *code, int args_size);

struct Sobj*
Sobj_set_func
(struct Sfunc *func);

int 
Sfunc_free
(struct Sfunc *func);

int 
Scall_context_free
(struct Scall_context *context);

struct Sfunc *
Sfunc_set
(struct Scode *code, int args_size, int code_size);

int Scall_context_free_frame(struct Scall_context *context);

#endif