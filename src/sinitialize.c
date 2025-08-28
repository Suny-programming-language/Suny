#include "sinitialize.h"

int 
Sinitialize_c_api_func
(
    struct Sframe *frame, 
    struct Scompiler *compiler, 
    struct Sc_api_func *api_func
) 

{
    struct Scope scope;
    scope.name = api_func->name;
    scope.address = api_func->address;
    scope.args_size = api_func->args_size;

    Sframe_load_c_api_func(frame, api_func->func, api_func->address, api_func->name, api_func->args_size);
    add_scope(compiler, api_func->name, api_func->address, api_func->args_size);

    return 0;
}

int SunyInitialize
(
    struct Sframe *frame, 
    struct Scompiler *compiler, 
    int address, 
    char* name, 
    int args_size, 
    void* func
) 

{
    struct Sc_api_func* api_func = Sc_api_func_set(func, name, address, args_size);
    return Sinitialize_c_api_func(frame, compiler, api_func);
}

int SunyInstallLib
(
    struct Sframe *frame, 
    struct Scompiler *compiler
)

{
    SunyInitialize(frame, compiler, 20, "print", 1, Sprintf);
    SunyInitialize(frame, compiler, 21, "exit", 1, Sexit);
    SunyInitialize(frame, compiler, 22, "load", 2, Sload_dll);
    return 0;
}