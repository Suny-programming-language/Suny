#include "slist.h"

int Slist_free(struct Slist* list) {
    for (int i = 0; i < list->count; i++) {
        struct Sobj* obj = list->array[i];
        dec_ref(obj);

        if (obj->gc->ref_count < 1) {
            Sobj_free(obj);
        }
    }
    
    free(list->array);
    free(list);
}

struct Slist* Slist_new(void) {
    struct Slist* list = malloc(sizeof(struct Slist));
    list->capacity = 1024;
    list->count = 0;
    list->start = NULL;
    list->end = NULL;
    list->array = calloc(list->capacity, sizeof(struct Sobj*));
    return list;
}

struct Slist* Slist_add(struct Slist* list, struct Sobj* obj) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->array = realloc(list->array, sizeof(struct Sobj*) * list->capacity);
    }

    list->array[list->count++] = obj;
    return list;
}

struct Sobj* Slist_get(struct Slist* list, int index) {
    return list->array[index];
}

struct Sobj* Sobj_make_list(struct Slist* list) {
    struct Sobj* obj = Sobj_new();
    obj->type = LIST_OBJ;
    obj->f_type = Stype_new();
    obj->f_type->f_list = list;
    return obj;
}

struct Slist* Slist_change_item(struct Slist* list, int index, struct Sobj* obj) {
    list->array[index] = obj;
    return list;
}

struct Slist* Slist_pop(struct Slist* list) {
    list->array[list->count - 1] = NULL;
    list->count -= 1;
    
    return list;
}

struct Slist* Slist_append(struct Slist* list1, struct Slist* list2) {
    struct Slist* list = Slist_new();

    for (int i = 0; i < list1->count; i++) {
        Slist_add(list, list1->array[i]);
    }

    for (int i = 0; i < list2->count; i++) {
        Slist_add(list, list2->array[i]);
    }

    return list;
}

struct Slist* Slist_mul(struct Slist* list1, int num) {
    struct Slist* list = Slist_new();

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < list1->count; j++) {
            Slist_add(list, list1->array[j]);
        }
    }

    return list;
}

struct Slist* Slist_range(int start, int end) {
    struct Slist* list = Slist_new();

    if (start > end) {
        for (int i = end; i < start; i++) {
            struct Sobj* value = Sobj_set_int(i);
            Sgc_inc_ref(value);
            Slist_add(list, value);
        }
    } else {
        for (int i = start; i < end; i++) {
            struct Sobj* value = Sobj_set_int(i);
            Sgc_inc_ref(value);
            Slist_add(list, value);
        }
    }

    return list;
}