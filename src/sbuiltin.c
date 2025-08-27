#include "sbuiltin.h"

struct Sc_api_func* 
Sc_api_func_set
(void* func, char* name, int address) {
    struct Sc_api_func* api_func = malloc(sizeof(struct Sc_api_func));
    api_func->func = func;
    api_func->name = name;
    api_func->address = address;
    api_func->args_size = 0;
    return api_func;
}

SUNY_API struct Sobj* Sprintf(struct Sframe* frame) {
    printf("Sprintf\n");
    return NULL;
}