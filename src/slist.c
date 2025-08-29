#include "slist.h"

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
    for (int i = 0; i < list->count; i++) {
        if (i == index) {
            return list->array[i];
        }
    }
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