#include "sio.h"

int Sio_write(struct Sobj *obj) {
    if (obj->type == STRING_OBJ) {
        printf("%s", obj->f_type->f_str->string);
    } else if (obj->type == LIST_OBJ) {
        printf("[");
        for (int i = 0; i < obj->f_type->f_list->count; i++) {
            struct Sobj *item = obj->f_type->f_list->array[i];
            Sio_write(item);
            if (i < obj->f_type->f_list->count - 1) {
                printf(", ");
            }
        }
        printf("]");
    } else if (obj->type == TRUE_OBJ) {
        printf("true");
    } else if (obj->type == FALSE_OBJ) {
        printf("false");
    } else if (obj->type == FUNC_OBJ) {
        printf("<function object %p defined in Suny VM at address %i>", obj->f_type->f_func, obj->address);
    }
    else {
        printf("%g", obj->value->value);
    }

    return 0;
}