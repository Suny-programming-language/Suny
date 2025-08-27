#ifndef SBUILTIN_H
#define SBUILTIN_H

#include "sobj.h"
#include "suny.h"
#include "scompile.h"

struct Sframe;

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

SUNY_API struct Sobj* Sprintf(struct Sframe* frame);

SUNY_API struct Sobj* Sexit(struct Sframe* frame);

#endif // SBUILTIN_H