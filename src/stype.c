#include "stype.h"

struct Stype *
Stype_new(void) {
    struct Stype *type = malloc(sizeof(struct Stype));
    type->f_type = Sobj_new();
    type->f_value = Sobj_new();
    type->f_size = 0;
    return type;
}

int 
Stype_free
(struct Stype *type) {
    type->f_type = NULL;
    type->f_value = NULL;
    type->f_size = 0;
    free(type);
    return 0;
}