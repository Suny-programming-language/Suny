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

int SunyInitialize_c_api_func
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
    SunyInitialize_c_api_func(frame, compiler, 20, "print", 1, Sprintf);
    SunyInitialize_c_api_func(frame, compiler, 21, "exit", 1, Sexit);
    SunyInitialize_c_api_func(frame, compiler, 22, "call", 3, Sload_dll);
    SunyInitialize_c_api_func(frame, compiler, 23, "push", 2, Spush);
    SunyInitialize_c_api_func(frame, compiler, 24, "pop", 1, Spop);
    SunyInitialize_c_api_func(frame, compiler, 25, "size", 1, Ssize);
    SunyInitialize_c_api_func(frame, compiler, 27, "range", 2, Srange);
    SunyInitialize_c_api_func(frame, compiler, 28, "read", 1, Sread);
    SunyInitialize_c_api_func(frame, compiler, 29, "puts", 1, Sputs);
    SunyInitialize_c_api_func(frame, compiler, 30, "number", 1, Snumber);
    
    return 0;
}

int Sunyloadlib_to_frame
(
    struct Sframe *frame,
    int address,
    int args_size,
    char* name,
    void* func
)

{
    struct Sc_api_func* api_func = Sc_api_func_set(func, name, address, args_size);
    Sframe_load_c_api_func(frame, api_func->func, api_func->address, api_func->name, api_func->args_size);
    return 0;
}
