#include "sobj.h"

struct Svalue* 
Svalue_new(void) {
    struct Svalue *value = malloc(sizeof(struct Svalue));
    value->value = 0;

    return value;
}

struct Sobj* 
Sobj_new(void) {
    struct Sobj *obj = malloc(sizeof(struct Sobj));

    obj->gc = Sgc_new();

    obj->dname = NULL;
    obj->ddoc = NULL;

    obj->type = NULL_OBJ;
    obj->value = Svalue_new();
    obj->size = 0;
    obj->address = 0;

    obj->f_value = NULL;
    obj->f_type = NULL;

    obj->meta = NULL;

    return obj;
}

int 
Sobj_free
(struct Sobj* obj) {
#ifdef DEBUG
    printf("[sobj.c] int Sobj_free(struct Sobj* obj) (building...)\n");
#endif
    if (obj->type == STRING_OBJ) {
        Sstr_free(obj->f_type->f_str);
        free(obj->f_type);
    }

    else if (obj->type == LIST_OBJ) {
        Slist_free(obj->f_type->f_list);
        free(obj->f_type);
    }

    else if (obj->type == FUNC_OBJ) {
        Sfunc_free(obj->f_type->f_func);
        free(obj->f_type);
    }

    free(obj->value);
    free(obj->gc);
    free(obj);

#ifdef DEBUG
    printf("[sobj.c] int Sobj_free(struct Sobj* obj) (done)\n");
#endif

    return 0;
}

struct Sobj*
Sobj_set_int
(float value) {
    struct Sobj *obj = Sobj_new();
    obj->type = NUMBER_OBJ;
    obj->value->value = value;
    return obj;
}

int
Sobj_free_objs
(struct Sobj** objs, int size) {
#ifdef DEBUG
    printf("[sobj.c] int Sobj_free_objs(struct Sobj** objs, int size) (building... %d)\n", size);
#endif
    for (int i = 0; i < size; i++) {
        Sobj_free(objs[i]);
    }
    
    free(objs);

#ifdef DEBUG
    printf("[sobj.c] int Sobj_free_objs(struct Sobj** objs, int size) (done %d)\n", size);
#endif
    return 0;
}