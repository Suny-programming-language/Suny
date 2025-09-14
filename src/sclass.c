#include "sclass.h"

struct Sclass*
Sclass_new
(void) {
    struct Sclass* sclass = malloc(sizeof(struct Sclass));

    sclass->count = 0;
    sclass->capacity = 1024;
    sclass->methods = malloc(sizeof(struct Sobj*) * sclass->capacity);

    return sclass;
}

int 
Sclass_free
(struct Sclass* sclass) {
    free(sclass->methods);
    free(sclass);
    return 0;
}

struct Sclass* 
Sclass_store_member
(struct Sclass* sclass, struct Sframe* frame, int address) {
    struct Sobj* obj = Sframe_pop(frame);

    struct Sobj* local = Sobj_new();
    local->type = LOCAL_OBJ;
    local->f_value = obj;
    local->address = address;

    return Sclass_store_object(sclass, local);
}

struct Sclass* 
Sclass_store_object
(struct Sclass* sclass, struct Sobj* object) {
    if (sclass->count >= sclass->capacity) {
        sclass->capacity *= 2;
        sclass->methods = realloc(sclass->methods, sizeof(struct Sobj*) * sclass->capacity);
    }

    sclass->methods[sclass->count++] = object;
    return sclass;
}

struct Sobj* 
Sclass_get_object
(struct Sclass* sclass, int address) {
    for (int i = 0; i < sclass->count; i++) {
        if (sclass->methods[i]->address == address) {
            return sclass->methods[i];
        }
    }

    return NULL;
}