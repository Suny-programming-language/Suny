#ifndef SINITIALIZE_H
#define SINITIALIZE_H

#include "score.h"
#include "scompile.h"
#include "sobj.h"

int 
Sinitialize_c_api_func 
(
    struct Sframe *frame, 
    struct Scompiler *compiler, 
    struct Sc_api_func *api_func
);

int SunyInitialize_c_api_func
(
    struct Sframe *frame, 
    struct Scompiler *compiler, 
    int address, 
    char* name, 
    int args_size, 
    void* func
);

int SunyInitialize_variable
(
    struct Sframe *frame, 
    struct Scompiler *compiler, 
    int address, 
    char* name,
    enum Sobj_t type,
    struct Sobj* value
);

int SunyInstallLib
(
    struct Sframe *frame, 
    struct Scompiler *compiler
);

int Sunyloadlib_to_frame
(
    struct Sframe *frame,
    int address,
    int args_size,
    char* name,
    void* func
);

#endif