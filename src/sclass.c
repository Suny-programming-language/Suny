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
(struct Sclass* sclass, struct Sobj* member) {
    if (sclass->count >= sclass->capacity) {
        sclass->capacity *= 2;
        sclass->methods = realloc(sclass->methods, sizeof(struct Sobj*) * sclass->capacity);
    }

    sclass->methods[sclass->count++] = member;
    return sclass;
}