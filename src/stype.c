#include "stype.h"

struct Stype *
Stype_new(void) {
    struct Stype *type = malloc(sizeof(struct Stype));

    type->f_call_context = NULL;
    type->f_code = NULL;
    type->f_frame = NULL;
    type->f_func = NULL;
    type->f_str = NULL;
    type->f_obj = NULL;
    type->f_bool = NULL;
    type->f_list = NULL;

    type->f_size = 0;
    return type;
}

int 
Stype_free
(struct Stype *type) {
    type->f_size = 0;
    free(type);
    return 0;
}