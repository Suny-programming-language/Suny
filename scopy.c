#include "scopy.h"

struct Sobj* Sobj_deep_copy(struct Sobj* obj) {
    struct Sobj* new_obj = Sobj_new();
    new_obj->type = obj->type;
    new_obj->f_type = Stype_new();
    new_obj->value->value = obj->value->value;
    new_obj->size = obj->size;
    new_obj->address = obj->address;
    new_obj->gc = Sgc_new();
    
    if (obj->type == STRING_OBJ) {
        new_obj->f_type->f_str = Sstr_new_from_char(obj->f_type->f_str->string, obj->f_type->f_str->size);
        new_obj->f_type->f_str->size = obj->f_type->f_str->size;
    } else if (obj->type == LIST_OBJ) {
        struct Slist* new_list = Slist_copy(obj->f_type->f_list);
        new_obj->f_type->f_list = new_list;
    } else if (obj->type == CLASS_OBJ) {
        struct Sclass* new_sclass = Sclass_copy(obj->f_type->f_class);
        new_obj->f_type->f_class = new_sclass;
    }

    return new_obj;
}

struct Sobj* Sobj_shallow_copy(struct Sobj* obj) {
    struct Sobj* new_obj = Sobj_new();
    new_obj->type = obj->type;
    new_obj->f_type = Stype_new();
    new_obj->value->value = obj->value->value;
    new_obj->size = obj->size;
    new_obj->address = obj->address;
    new_obj->f_type = obj->f_type;
    return new_obj;
}

struct Slist* Slist_copy(struct Slist* list) {
    struct Slist* new_list = Slist_new();
    for (int i = 0; i < list->count; i++) {
        Slist_add(new_list, Sobj_deep_copy(list->array[i]));
    }
    return new_list;
}

struct Sclass* Sclass_copy(struct Sclass* sclass) {
    struct Sclass* new_sclass = Sclass_new();

    for (int i = 0; i < sclass->count; i++) {
        struct Sobj* new_obj = Sobj_deep_copy(sclass->methods[i]->f_value);

        struct Sobj* method = Sobj_new();
        method->type = LOCAL_OBJ;
        method->f_value = new_obj;
        method->address = sclass->methods[i]->address;

        Sclass_push_obj(new_sclass, method);
    }

    return new_sclass;
}