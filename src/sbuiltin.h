#ifndef SBUILTIN_H
#define SBUILTIN_H

#include "scompile.h"
#include "stool.h"
#include "slist.h"
#include "sio.h"

struct Sframe;
struct Scompiler;

typedef struct Sobj* (*builtin_func)(struct Sframe*);

typedef struct Sframe* (*main_func)(struct Sframe*, struct Scompiler*);

#define call_func(func, frame) ((struct Sobj* (*)(struct Sframe*)) (func))((frame));

#define load_c_api_func(f_obj) (f_obj)->c_api_func->func;

struct Sc_api_func {
    void* func;
    char* name;
    int address;
    int args_size;
};

struct Sc_api_func* 
Sc_api_func_set
(   
    void* func, 
    char* name, 
    int address,
    int args_size
);

struct Sc_api_func* 
Sc_api_func_set
(void* func, char* name, int address, int args_size);

struct Sobj* Sprintf(struct Sframe* frame);

struct Sobj* Sexit(struct Sframe* frame);

struct Sobj* Sputs(struct Sframe* frame);

struct Sobj* Sread(struct Sframe* frame);

struct Sobj* Snumber(struct Sframe* frame);

struct Sobj* Ssize(struct Sframe* frame);

struct Sobj* Spush(struct Sframe* frame);

struct Sobj* Spop(struct Sframe* frame);

struct Sobj *Sload_dll(struct Sframe *frame);

struct Sobj *Sisdigit_builtin(struct Sframe *frame);

struct Sobj *Srange(struct Sframe *frame);

#endif // SBUILTIN_H