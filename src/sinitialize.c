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

    Sframe_load_c_api_func(frame, api_func->func, api_func->address, api_func->name);
    add_scope(compiler, api_func->name, api_func->address, api_func->args_size);

    return 0;
}