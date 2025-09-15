#include "../src/Suny.h"

#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

#ifndef E
#define E 2.71828182845904523536
#endif

// ================= Vector Library =================

#define DOC "Mathematical vector operations"
#define LIB_NAME "vector"

#define vector_set_meta(obj) \
    obj->meta = malloc(sizeof(struct Smeta)); \
    obj->meta->mm_add = Sobj_add_vector; \
    obj->meta->mm_sub = Sobj_sub_vector; \
    obj->meta->mm_mul = Sobj_mul_vector; \
    obj->meta->mm_div = Sobj_div_vector; \
    obj->meta->mm_tostring = Sobj_print_vector; \

struct Svector {
    struct Sobj** items;
    int capacity;
    int count;
};

struct Svector* Svector_new(void) {
    struct Svector* vec = malloc(sizeof(struct Svector));
    vec->capacity = 4;
    vec->count = 0;
    vec->items = malloc(sizeof(struct Sobj*) * vec->capacity);
    return vec;
}

void Svector_push(struct Svector* vec, struct Sobj* item) {
    if (vec->count >= vec->capacity) {
        vec->capacity *= 2;
        vec->items = realloc(vec->items, sizeof(struct Sobj*) * vec->capacity);
    }
    vec->items[vec->count++] = item;
}

void Svector_free(struct Svector* vec) {
    free(vec->items);
    free(vec);
}

struct Svector* Svector_add(struct Svector* v1, struct Svector* v2) {
    if (v1->count != v2->count) {
        fprintf(stderr, "Error: Vectors must be of the same length for addition.\n");
        return NULL;
    }

    struct Svector* result = Svector_new();
    for (int i = 0; i < v1->count; i++) {
        struct Sobj* item = Seval_add(v1->items[i], v2->items[i]);
        Svector_push(result, item);
    }

    return result;
}

struct Svector* Svector_sub(struct Svector* v1, struct Svector* v2) {
    if (v1->count != v2->count) {
        fprintf(stderr, "Error: Vectors must be of the same length for subtraction.\n");
        return NULL;
    }

    struct Svector* result = Svector_new();
    for (int i = 0; i < v1->count; i++) {
        struct Sobj* item = Seval_sub(v1->items[i], v2->items[i]);
        Svector_push(result, item);
    }

    return result;
}

struct Svector* Svector_mul(struct Svector* v1, struct Svector* v2) {
    if (v1->count != v2->count) {
        fprintf(stderr, "Error: Vectors must be of the same length for multiplication.\n");
        return NULL;
    }

    struct Svector* result = Svector_new();
    for (int i = 0; i < v1->count; i++) {
        struct Sobj* item = Seval_mul(v1->items[i], v2->items[i]);
        Svector_push(result, item);
    }

    return result;
}

struct Svector* Svector_div(struct Svector* v1, struct Svector* v2) {
    if (v1->count != v2->count) {
        fprintf(stderr, "Error: Vectors must be of the same length for division.\n");
        return NULL;
    }

    struct Svector* result = Svector_new();
    for (int i = 0; i < v1->count; i++) {
        struct Sobj* item = Seval_div(v1->items[i], v2->items[i]);
        Svector_push(result, item);
    }

    return result;
}

void Svector_print(struct Svector* vec) {
    printf("vector(");
    for (int i = 0; i < vec->count; i++) {
        struct Sobj* item = vec->items[i];
        Sio_write(item);
        if (i < vec->count - 1) {
            printf(", ");
        }
    }
    printf(")");
}

struct Sobj* Sobj_add_vector(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type != USER_DATA_OBJ || obj2->type != USER_DATA_OBJ) {
        fprintf(stderr, "Error: Both operands must be vectors for addition.\n");
        return NULL;
    }

    struct Svector* v1 = obj1->f_type->f_userdata->data;
    struct Svector* v2 = obj2->f_type->f_userdata->data;

    struct Svector* result_vec = Svector_add(v1, v2);
    if (!result_vec) return NULL;

    struct Sobj* result_obj = Sobj_make_userdata(result_vec);
    result_obj->meta = obj1->meta;

    return result_obj;
}

struct Sobj* Sobj_sub_vector(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type != USER_DATA_OBJ || obj2->type != USER_DATA_OBJ) {
        fprintf(stderr, "Error: Both operands must be vectors for subtraction.\n");
        return NULL;
    }

    struct Svector* v1 = obj1->f_type->f_userdata->data;
    struct Svector* v2 = obj2->f_type->f_userdata->data;

    struct Svector* result_vec = Svector_sub(v1, v2);
    if (!result_vec) return NULL;

    struct Sobj* result_obj = Sobj_make_userdata(result_vec);
    result_obj->meta = obj1->meta;

    return result_obj;
}

struct Sobj* Sobj_mul_vector(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj2->type == NUMBER_OBJ) {
        struct Svector* v1 = obj1->f_type->f_userdata->data;
        struct Svector* result_vec = Svector_new();
        for (int i = 0; i < v1->count; i++) {
            struct Sobj* item = Seval_mul(v1->items[i], obj2);
            Svector_push(result_vec, item);
        }
        struct Sobj* result_obj = Sobj_make_userdata(result_vec);
        result_obj->meta = obj1->meta;
        return result_obj;
    }

    struct Svector* v1 = obj1->f_type->f_userdata->data;
    struct Svector* v2 = obj2->f_type->f_userdata->data;

    struct Svector* result_vec = Svector_mul(v1, v2);
    if (!result_vec) return NULL;

    struct Sobj* result_obj = Sobj_make_userdata(result_vec);
    result_obj->meta = obj1->meta;

    return result_obj;
}

struct Sobj* Sobj_div_vector(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj2->type == NUMBER_OBJ) {
        struct Svector* v1 = obj1->f_type->f_userdata->data;
        struct Svector* result_vec = Svector_new();
        for (int i = 0; i < v1->count; i++) {
            struct Sobj* item = Seval_div(v1->items[i], obj2);
            Svector_push(result_vec, item);
        }
        struct Sobj* result_obj = Sobj_make_userdata(result_vec);
        result_obj->meta = obj1->meta;
        return result_obj;
    }

    struct Svector* v1 = obj1->f_type->f_userdata->data;
    struct Svector* v2 = obj2->f_type->f_userdata->data;

    struct Svector* result_vec = Svector_div(v1, v2);
    if (!result_vec) return NULL;

    struct Sobj* result_obj = Sobj_make_userdata(result_vec);
    result_obj->meta = obj1->meta;

    return result_obj;
}

struct Sobj* Sobj_print_vector(struct Sobj* obj) {
    if (obj->type != USER_DATA_OBJ) {
        fprintf(stderr, "Error: Object is not a vector for printing.\n");
        return NULL;
    }

    struct Svector* vec = obj->f_type->f_userdata->data;
    Svector_print(vec);

    return obj;
}

struct Sobj* Sobj_make_vector(struct Sframe* frame) {
    struct Sobj* list = Sframe_pop(frame);

    if (list->type != LIST_OBJ) {
        fprintf(stderr, "Error: Expected a list to create a vector.\n");
        return NULL;
    }

    struct Svector* vec = Svector_new();
    for (int i = 0; i < list->f_type->f_list->count; i++) {
        Svector_push(vec, list->f_type->f_list->array[i]);
    }

    struct Sobj* vec_obj = Sobj_make_userdata(vec);

    vector_set_meta(vec_obj);
    
    return vec_obj;
}

// ================ End of Vector Library =================

// ================ Math Functions =================

struct Sobj* Scos(struct Sframe* frame) {
    struct Sobj* angle = Sframe_pop(frame);
    float result = cosf(angle->value->value);
    return Sobj_set_int(result);
}

struct Sobj* Ssin(struct Sframe* frame) {
    struct Sobj* angle = Sframe_pop(frame);
    float result = sinf(angle->value->value);
    return Sobj_set_int(result);
}

struct Sobj* Stan(struct Sframe* frame) {
    struct Sobj* angle = Sframe_pop(frame);
    float result = tanf(angle->value->value);
    return Sobj_set_int(result);
}

struct Sobj* Scot(struct Sframe* frame) {
    struct Sobj* angle = Sframe_pop(frame);
    float result = 1 / tanf(angle->value->value);
    return Sobj_set_int(result);
}

// ================ End of Math Functions =================

SUNY_API struct Sframe* Smain(struct Sframe* frame, struct Scompiler* compiler) {
    SunyInitialize_variable(frame, compiler, 30, "pi", NUMBER_OBJ, Sobj_set_int(PI));
    SunyInitialize_variable(frame, compiler, 31, "e", NUMBER_OBJ, Sobj_set_int(E));
 
    SunyInitialize_c_api_func(frame, compiler, 33, "vector", 1, Sobj_make_vector);

    SunyInitialize_c_api_func(frame, compiler, 34, "cos", 1, Scos);
    SunyInitialize_c_api_func(frame, compiler, 35, "sin", 1, Ssin);
    SunyInitialize_c_api_func(frame, compiler, 36, "tan", 1, Stan);
    SunyInitialize_c_api_func(frame, compiler, 37, "cot", 1, Scot);
    
    return frame;
}