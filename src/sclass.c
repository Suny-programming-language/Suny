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
Sclass_store_object
(struct Sclass* sclass, struct Sframe* frame, int address) {
    struct Sobj* object = Sframe_pop(frame);

    if (sclass->count == sclass->capacity) {
        sclass->capacity *= 2;
        sclass->methods = realloc(sclass->methods, sizeof(struct Sobj*) * sclass->capacity);
    }

    for (int i = 0; i < sclass->count; i++) {
        if (sclass->methods[i]->address == address) {
            dec_ref(sclass->methods[i]->f_value);
            sclass->methods[i]->f_value = object;
            return sclass;
        }
    }

    struct Sobj* method = Sobj_new();
    method->type = LOCAL_OBJ;
    method->f_value = object;
    method->address = address;

    sclass->methods[sclass->count++] = method;
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

struct Sobj*
Sobj_make_class(struct Sclass* sclass) {
    struct Sobj* obj = Sobj_new();
    obj->type = CLASS_OBJ;
    obj->f_type = Stype_new();
    obj->f_type->f_class = sclass;
    return obj;
}

struct Sobj* 
Sclass_push_obj
(struct Sclass* sclass, struct Sobj* obj) {
    if (sclass->count == sclass->capacity) {
        sclass->capacity *= 2;
        sclass->methods = realloc(sclass->methods, sizeof(struct Sobj*) * sclass->capacity);
    }

    sclass->methods[sclass->count++] = obj;
    return obj;
}



struct Sclass* 
Sclass_store_member
(struct Sclass* sclass, struct Sframe* frame, struct Sobj* value, int address) {
    for (int i = 0; i < sclass->count; i++) {
        if (sclass->methods[i]->address == address) {
            dec_ref(sclass->methods[i]->f_value);

            Sgc_dec_ref(sclass->methods[i]->f_value, frame->gc_pool);

            sclass->methods[i]->f_value = value;
            return sclass;
        }
    }

    struct Sobj* method = Sobj_new();
    method->type = LOCAL_OBJ;
    method->f_value = value;
    method->address = address;

    sclass->methods[sclass->count++] = method;
    
    return NULL;
}
