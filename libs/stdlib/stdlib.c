#include "C:/Suny/Suny.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

#ifndef E
#define E 2.71828182845904523536
#endif

// ================= Vector Library =================

struct Svector {
    struct Sobj** items;
    int capacity;
    int count;
};

int Svector_free(struct Svector* vec) {
    Sobj_free_objs(vec->items, vec->count);
    free(vec);
    return 0;
}

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

int Sobj_free_vector(struct Sobj* vec) {
    Svector_free(vec->f_type->f_userdata->data);
    return 0;
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

    vec_obj->meta = Smeta_new();
    vec_obj->meta->mm_add = Sobj_add_vector;
    vec_obj->meta->mm_sub = Sobj_sub_vector;
    vec_obj->meta->mm_mul = Sobj_mul_vector;
    vec_obj->meta->mm_div = Sobj_div_vector;
    vec_obj->meta->mm_tostring = Sobj_print_vector;
    vec_obj->meta->mm_free = Sobj_free_vector;
    
    return vec_obj;
}

// ================ End of Vector Library =================

// ================ Complex Library =======================

struct Scomplex {
    float real;
    float imag;
};

struct Scomplex* Scomplex_new(float real, float imag) {
    struct Scomplex* comp = malloc(sizeof(struct Scomplex));
    comp->real = real;
    comp->imag = imag;
    return comp;
}

struct Scomplex* Scomplex_add(struct Scomplex* comp1, struct Scomplex* comp2) {
    float real = comp1->real + comp2->real;
    float imag = comp1->imag + comp2->imag;
    return Scomplex_new(real, imag);
}

struct Scomplex* Scomplex_sub(struct Scomplex* comp1, struct Scomplex* comp2) {
    float real = comp1->real - comp2->real;
    float imag = comp1->imag - comp2->imag;
    return Scomplex_new(real, imag);
}

struct Scomplex* Scomplex_mul(struct Scomplex* comp1, struct Scomplex* comp2) {
    float real = comp1->real * comp2->real - comp1->imag * comp2->imag;
    float imag = comp1->real * comp2->imag + comp1->imag * comp2->real;
    return Scomplex_new(real, imag);
}

struct Scomplex* Scomplex_div(struct Scomplex* comp1, struct Scomplex* comp2) {
    float denom = comp2->real * comp2->real + comp2->imag * comp2->imag;
    if (denom == 0) {
        fprintf(stderr, "Error: Division by zero in complex division.\n");
        return NULL;
    }
    float real = (comp1->real * comp2->real + comp1->imag * comp2->imag) / denom;
    float imag = (comp1->imag * comp2->real - comp1->real * comp2->imag) / denom;
    return Scomplex_new(real, imag);
}

void Scomplex_print(struct Scomplex* comp) {
    if (comp->imag >= 0) {
        printf("%g + %gi", comp->real, comp->imag);
    } else {
        printf("%g - %gi", comp->real, -comp->imag);
    }
}

struct Sobj* Sobj_print_complex(struct Sobj* obj) {
    if (obj->type != USER_DATA_OBJ) {
        fprintf(stderr, "Error: Object is not a complex number for printing.\n");
        return NULL;
    }

    struct Scomplex* comp = obj->f_type->f_userdata->data;
    Scomplex_print(comp);

    return obj;
}

struct Sobj* Sobj_add_complex(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type == USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        struct Scomplex* comp1 = obj1->f_type->f_userdata->data;
        struct Scomplex* comp2 = obj2->f_type->f_userdata->data;
        struct Scomplex* result_comp = Scomplex_add(comp1, comp2);
        if (!result_comp) return NULL;
        struct Sobj* result_obj = Sobj_make_userdata(result_comp);
        result_obj->meta = obj1->meta;
        return result_obj;
    } else if (obj1->type == USER_DATA_OBJ && obj2->type != USER_DATA_OBJ) {
        struct Scomplex* comp1 = obj1->f_type->f_userdata->data;
        struct Scomplex* comp2 = Scomplex_new(obj2->value->value, 0);
        struct Scomplex* result_comp = Scomplex_add(comp1, comp2);
        if (!result_comp) return NULL;
        struct Sobj* result_obj = Sobj_make_userdata(result_comp);
        result_obj->meta = obj1->meta;
        free(comp2);
        return result_obj;
    } else if (obj1->type != USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        struct Scomplex* comp1 = Scomplex_new(obj1->value->value, 0);
        struct Scomplex* comp2 = obj2->f_type->f_userdata->data;
        struct Scomplex* result_comp = Scomplex_add(comp1, comp2);
        if (!result_comp) return NULL;
        struct Sobj* result_obj = Sobj_make_userdata(result_comp);
        result_obj->meta = obj2->meta;
        free(comp1);
        return result_obj;
    } else {
        fprintf(stderr, "Error: At least one operand must be a complex number for addition.\n");
        return NULL;
    }
}

struct Sobj* Sobj_sub_complex(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type == USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        struct Scomplex* comp1 = obj1->f_type->f_userdata->data;
        struct Scomplex* comp2 = obj2->f_type->f_userdata->data;
        struct Scomplex* result_comp = Scomplex_sub(comp1, comp2);
        if (!result_comp) return NULL;
        struct Sobj* result_obj = Sobj_make_userdata(result_comp);
        result_obj->meta = obj1->meta;
        return result_obj;
    } else if (obj1->type == USER_DATA_OBJ && obj2->type != USER_DATA_OBJ) {
        struct Scomplex* comp1 = obj1->f_type->f_userdata->data;
        struct Scomplex* comp2 = Scomplex_new(obj2->value->value, 0);
        struct Scomplex* result_comp = Scomplex_sub(comp1, comp2);
        if (!result_comp) return NULL;
        struct Sobj* result_obj = Sobj_make_userdata(result_comp);
        result_obj->meta = obj1->meta;
        free(comp2);
        return result_obj;
    } else if (obj1->type != USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        struct Scomplex* comp1 = Scomplex_new(obj1->value->value, 0);
        struct Scomplex* comp2 = obj2->f_type->f_userdata->data;
        struct Scomplex* result_comp = Scomplex_sub(comp1, comp2);
        if (!result_comp) return NULL;
        struct Sobj* result_obj = Sobj_make_userdata(result_comp);
        result_obj->meta = obj2->meta;
        free(comp1);
        return result_obj;
    } else {
        fprintf(stderr, "Error: At least one operand must be a complex number for subtraction.\n");
        return NULL;
    }
}

struct Sobj* Sobj_mul_complex(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type == USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        struct Scomplex* comp1 = obj1->f_type->f_userdata->data;
        struct Scomplex* comp2 = obj2->f_type->f_userdata->data;
        struct Scomplex* result_comp = Scomplex_mul(comp1, comp2);
        if (!result_comp) return NULL;
        struct Sobj* result_obj = Sobj_make_userdata(result_comp);
        result_obj->meta = obj1->meta;
        return result_obj;
    } else if (obj1->type == USER_DATA_OBJ && obj2->type != USER_DATA_OBJ) {
        struct Scomplex* comp1 = obj1->f_type->f_userdata->data;
        struct Scomplex* comp2 = Scomplex_new(obj2->value->value, 0);
        struct Scomplex* result_comp = Scomplex_mul(comp1, comp2);
        if (!result_comp) return NULL;
        struct Sobj* result_obj = Sobj_make_userdata(result_comp);
        result_obj->meta = obj1->meta;
        free(comp2);
        return result_obj;
    } else if (obj1->type != USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        struct Scomplex* comp1 = Scomplex_new(obj1->value->value, 0);
        struct Scomplex* comp2 = obj2->f_type->f_userdata->data;
        struct Scomplex* result_comp = Scomplex_mul(comp1, comp2);
        if (!result_comp) return NULL;
        struct Sobj* result_obj = Sobj_make_userdata(result_comp);
        result_obj->meta = obj2->meta;
        free(comp1);
        return result_obj;
    } else {
        fprintf(stderr, "Error: At least one operand must be a complex number for multiplication.\n");
        return NULL;
    }
}

struct Sobj* Sobj_div_complex(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type == USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        struct Scomplex* comp1 = obj1->f_type->f_userdata->data;
        struct Scomplex* comp2 = obj2->f_type->f_userdata->data;
        struct Scomplex* result_comp = Scomplex_div(comp1, comp2);
        if (!result_comp) return NULL;
        struct Sobj* result_obj = Sobj_make_userdata(result_comp);
        result_obj->meta = obj1->meta;
        return result_obj;
    } else if (obj1->type == USER_DATA_OBJ && obj2->type != USER_DATA_OBJ) {
        struct Scomplex* comp1 = obj1->f_type->f_userdata->data;
        struct Scomplex* comp2 = Scomplex_new(obj2->value->value, 0);
        struct Scomplex* result_comp = Scomplex_div(comp1, comp2);
        if (!result_comp) return NULL;
        struct Sobj* result_obj = Sobj_make_userdata(result_comp);
        result_obj->meta = obj1->meta;
        free(comp2);
        return result_obj;
    } else if (obj1->type != USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        struct Scomplex* comp1 = Scomplex_new(obj1->value->value, 0);
        struct Scomplex* comp2 = obj2->f_type->f_userdata->data;
        struct Scomplex* result_comp = Scomplex_div(comp1, comp2);
        if (!result_comp) return NULL;
        struct Sobj* result_obj = Sobj_make_userdata(result_comp);
        result_obj->meta = obj2->meta;
        free(comp1);
        return result_obj;
    } else {
        fprintf(stderr, "Error: At least one operand must be a complex number for division.\n");
        return NULL;
    }
}

struct Sobj* Sobj_make_complex(struct Sframe* frame) {
    struct Sobj* imag_obj = Sframe_pop(frame);
    struct Sobj* real_obj = Sframe_pop(frame);

    if (real_obj->type != NUMBER_OBJ || imag_obj->type != NUMBER_OBJ) {
        fprintf(stderr, "Error: Expected two numbers to create a complex number.\n");
        return NULL;
    }

    struct Scomplex* comp = Scomplex_new(real_obj->value->value, imag_obj->value->value);
    struct Sobj* comp_obj = Sobj_make_userdata(comp);

    comp_obj->meta = Smeta_new();
    comp_obj->meta->mm_add = Sobj_add_complex;
    comp_obj->meta->mm_sub = Sobj_sub_complex;
    comp_obj->meta->mm_mul = Sobj_mul_complex;
    comp_obj->meta->mm_div = Sobj_div_complex;
    comp_obj->meta->mm_tostring = Sobj_print_complex;

    return comp_obj;
}

// ================ End of Complex Library ================

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

// ================ Big Integer Functions =================

struct Sbigint {
    char* digits; // string representation of the big integer
    int length;   // number of digits
    int capacity; // allocated capacity
};

static void Sbigint_trim(struct Sbigint* bigint) {
    int i = 0;
    while (i < bigint->length - 1 && bigint->digits[i] == '0') {
        i++;
    }
    if (i > 0) {
        memmove(bigint->digits, bigint->digits + i, bigint->length - i + 1);
        bigint->length -= i;
    }
}

struct Sbigint* Sbigint_new(const char* str) {
    struct Sbigint* bigint = malloc(sizeof(struct Sbigint));
    bigint->length = strlen(str);
    bigint->capacity = bigint->length + 1;
    bigint->digits = malloc(bigint->capacity);
    strcpy(bigint->digits, str);
    Sbigint_trim(bigint);
    return bigint;
}

int Sbigint_free(struct Sbigint* bigint) {
    if (!bigint) return 0;
    free(bigint->digits);
    free(bigint);
    return 1;
}

int Sobj_free_bigint(struct Sobj* obj) {
    Sbigint_free(obj->f_type->f_userdata->data);
    return 1;
}

int Sbigint_cmp(struct Sbigint* bigint1, struct Sbigint* bigint2) {
    if (bigint1->length != bigint2->length) {
        return (bigint1->length > bigint2->length) ? 1 : -1;
    }
    return strcmp(bigint1->digits, bigint2->digits);
}

int Sbigint_to_int(struct Sbigint* bigint) {
    int result = 0;
    for (int i = 0; i < bigint->length; i++) {
        result = result * 10 + bigint->digits[i] - '0';
    }
    return result;
}

int Sbigint_bigger(struct Sbigint* bigint1, struct Sbigint* bigint2) {
    return Sbigint_cmp(bigint1, bigint2) > 0;
}

int Sbigint_smaller(struct Sbigint* bigint1, struct Sbigint* bigint2) {
    return Sbigint_cmp(bigint1, bigint2) < 0;
}

int Sbigint_equal(struct Sbigint* bigint1, struct Sbigint* bigint2) {
    return Sbigint_cmp(bigint1, bigint2) == 0;
}

int Sbigint_not_equal(struct Sbigint* bigint1, struct Sbigint* bigint2) {
    return Sbigint_cmp(bigint1, bigint2) != 0;
}

int Sbigint_bigger_equal(struct Sbigint* bigint1, struct Sbigint* bigint2) {
    return Sbigint_cmp(bigint1, bigint2) >= 0;
}

int Sbigint_smaller_equal(struct Sbigint* bigint1, struct Sbigint* bigint2) {
    return Sbigint_cmp(bigint1, bigint2) <= 0;
}

struct Sbigint* Sbigint_add(struct Sbigint* bigint1, struct Sbigint* bigint2) {
    int max_len = (bigint1->length > bigint2->length ? bigint1->length : bigint2->length) + 1;
    char* result = malloc(max_len + 1);
    result[max_len] = '\0';

    int carry = 0;
    int i = bigint1->length - 1;
    int j = bigint2->length - 1;
    int k = max_len - 1;

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? bigint1->digits[i--] - '0' : 0;
        int digit2 = (j >= 0) ? bigint2->digits[j--] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        result[k--] = (sum % 10) + '0';
        carry = sum / 10;
    }

    struct Sbigint* sum_bigint = Sbigint_new(result + k + 1);
    free(result);
    return sum_bigint;
}
struct Sbigint* Sbigint_sub(struct Sbigint* bigint1, struct Sbigint* bigint2) {
    int cmp = Sbigint_cmp(bigint1, bigint2);

    if (cmp == 0) {
        return Sbigint_new("0");
    }

    struct Sbigint* bigger;
    struct Sbigint* smaller;
    int result_sign = 0;

    if (cmp > 0) { 
        bigger = bigint1; 
        smaller = bigint2;
    } else { 
        bigger = bigint2; 
        smaller = bigint1; 
        result_sign = 1;
    }

    int max_len = bigger->length;
    char* result = malloc(max_len + 1);
    result[max_len] = '\0';

    int borrow = 0;
    int i = bigger->length - 1;
    int j = smaller->length - 1;
    int k = max_len - 1;

    while (i >= 0) {
        int digit1 = bigger->digits[i--] - '0';
        int digit2 = (j >= 0) ? smaller->digits[j--] - '0' : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[k--] = diff + '0';
    }

    char* final_result = result;
    while (*final_result == '0' && *(final_result + 1) != '\0') {
        final_result++;
    }

    struct Sbigint* diff_bigint = Sbigint_new(final_result);
    free(result);
    return diff_bigint;
}

struct Sbigint* Sbigint_mul(struct Sbigint* bigint1, struct Sbigint* bigint2) {
    int n = bigint1->length;
    int m = bigint2->length;
    int* temp = calloc(n + m, sizeof(int));

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int mul = (bigint1->digits[i] - '0') * (bigint2->digits[j] - '0');
            int sum = temp[i + j + 1] + mul;
            temp[i + j + 1] = sum % 10;
            temp[i + j] += sum / 10;
        }
    }

    int start = 0;
    while (start < n + m - 1 && temp[start] == 0) start++;
    char* result = malloc(n + m - start + 1);
    for (int i = start; i < n + m; i++) {
        result[i - start] = temp[i] + '0';
    }
    result[n + m - start] = '\0';

    free(temp);
    struct Sbigint* mul_bigint = Sbigint_new(result);
    free(result);
    return mul_bigint;
}

struct Sbigint* Sbigint_div(struct Sbigint* bigint1, struct Sbigint* bigint2) {
    if (Sbigint_cmp(bigint2, Sbigint_new("0")) == 0) {
        printf("Error: Division by zero\n");
        return NULL;
    }

    struct Sbigint* quotient = Sbigint_new("0");
    struct Sbigint* remainder = Sbigint_new("0");

    for (int i = 0; i < bigint1->length; i++) {
        char digit_str[2] = { bigint1->digits[i], '\0' };
        struct Sbigint* tmp = Sbigint_mul(remainder, Sbigint_new("10"));
        struct Sbigint* tmp2 = Sbigint_add(tmp, Sbigint_new(digit_str));
        Sbigint_free(remainder);
        remainder = tmp2;
        Sbigint_free(tmp);

        int count = 0;
        while (Sbigint_cmp(remainder, bigint2) >= 0) {
            struct Sbigint* tmp3 = Sbigint_sub(remainder, bigint2);
            Sbigint_free(remainder);
            remainder = tmp3;
            count++;
        }

        int qlen = quotient->length;
        quotient->digits = realloc(quotient->digits, qlen + 2);
        quotient->digits[qlen] = count + '0';
        quotient->digits[qlen + 1] = '\0';
        quotient->length++;
    }

    Sbigint_trim(quotient);
    Sbigint_free(remainder);
    return quotient;
}

char* float_to_string(float num) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.0f", num);
    return strdup(buffer);
}

struct Sobj* Sobj_print_bigint(struct Sobj* obj) {
    if (obj->type != USER_DATA_OBJ) {
        fprintf(stderr, "Error: Object is not a big integer for printing.\n");
        return NULL;
    }

    struct Sbigint* bigint = obj->f_type->f_userdata->data;
    printf("%s", bigint->digits);

    return obj;
}

struct Sobj* Sobj_add_bigint(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type == USER_DATA_OBJ && obj2->type != USER_DATA_OBJ) {
        char* buffer = float_to_string(obj2->value->value);
        struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
        struct Sbigint* bigint2 = Sbigint_new(buffer);
        bigint2->digits[0] = (char)(obj2->value->value + '0');
        bigint2->length = 1;
        struct Sbigint* sum_bigint = Sbigint_add(bigint1, bigint2);
        Sbigint_free(bigint2);
        if (!sum_bigint) return NULL;
        struct Sobj* sum_obj = Sobj_make_userdata(sum_bigint);
        sum_obj->meta = obj1->meta;
        return sum_obj;
    } else if (obj1->type != USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        char* buffer = float_to_string(obj1->value->value);
        struct Sbigint* bigint1 = Sbigint_new(buffer);
        bigint1->digits[0] = (char)(obj1->value->value + '0');
        bigint1->length = 1;
        struct Sbigint* sum_bigint = Sbigint_add(bigint1, obj2->f_type->f_userdata->data);
        Sbigint_free(bigint1);
        if (!sum_bigint) return NULL;
        struct Sobj* sum_obj = Sobj_make_userdata(sum_bigint);
        sum_obj->meta = obj2->meta;
        return sum_obj;
    } else if (obj1->type == USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
        struct Sbigint* bigint2 = obj2->f_type->f_userdata->data;

        struct Sbigint* sum_bigint = Sbigint_add(bigint1, bigint2);
        if (!sum_bigint) return NULL;

        struct Sobj* sum_obj = Sobj_make_userdata(sum_bigint);
        sum_obj->meta = obj1->meta;
        return sum_obj;
    } else {
        fprintf(stderr, "Error: At least one operand must be a big integer for addition.\n");
        return NULL;
    }
}

struct Sobj* Sobj_sub_bigint(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type == USER_DATA_OBJ && obj2->type != USER_DATA_OBJ) {
        char* buffer = float_to_string(obj2->value->value);

        struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
        struct Sbigint* bigint2 = Sbigint_new(buffer);
        bigint2->digits[0] = (char)(obj2->value->value + '0');
        bigint2->length = 1;
        struct Sbigint* sub_bigint = Sbigint_sub(bigint1, bigint2);
        Sbigint_free(bigint2);
        if (!sub_bigint) return NULL;
        struct Sobj* sub_obj = Sobj_make_userdata(sub_bigint);
        sub_obj->meta = obj1->meta;
        return sub_obj;
    } else if (obj1->type != USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        char* buffer = float_to_string(obj1->value->value);

        struct Sbigint* bigint1 = Sbigint_new(buffer);
        bigint1->digits[0] = (char)(obj1->value->value + '0');
        bigint1->length = 1;
        struct Sbigint* sub_bigint = Sbigint_sub(bigint1, obj2->f_type->f_userdata->data);
        Sbigint_free(bigint1);
        if (!sub_bigint) return NULL;
        struct Sobj* sub_obj = Sobj_make_userdata(sub_bigint);
        sub_obj->meta = obj2->meta;
        return sub_obj;
    } else if (obj1->type == USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
        struct Sbigint* bigint2 = obj2->f_type->f_userdata->data;

        struct Sbigint* sub_bigint = Sbigint_sub(bigint1, bigint2);
        if (!sub_bigint) return NULL;

        struct Sobj* sub_obj = Sobj_make_userdata(sub_bigint);
        sub_obj->meta = obj1->meta;
        return sub_obj;
    } else {
        fprintf(stderr, "Error: At least one operand must be a big integer for subtraction.\n");
        return NULL;
    }
}

struct Sobj* Sobj_mul_bigint(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type == USER_DATA_OBJ && obj2->type != USER_DATA_OBJ) {
        char* buffer = float_to_string(obj2->value->value);
        struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
        struct Sbigint* bigint2 = Sbigint_new(buffer);
        bigint2->digits[0] = (char)(obj2->value->value + '0');
        bigint2->length = 1;
        struct Sbigint* mul_bigint = Sbigint_mul(bigint1, bigint2);
        Sbigint_free(bigint2);
        if (!mul_bigint) return NULL;
        struct Sobj* mul_obj = Sobj_make_userdata(mul_bigint);
        mul_obj->meta = obj1->meta;
        return mul_obj;
    } else if (obj1->type != USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        char* buffer = float_to_string(obj1->value->value);
        struct Sbigint* bigint1 = Sbigint_new(buffer);
        bigint1->digits[0] = (char)(obj1->value->value + '0');
        bigint1->length = 1;
        struct Sbigint* mul_bigint = Sbigint_mul(bigint1, obj2->f_type->f_userdata->data);
        Sbigint_free(bigint1);
        if (!mul_bigint) return NULL;
        struct Sobj* mul_obj = Sobj_make_userdata(mul_bigint);
        mul_obj->meta = obj2->meta;
        return mul_obj;
    } else if (obj1->type == USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
        struct Sbigint* bigint2 = obj2->f_type->f_userdata->data;

        struct Sbigint* mul_bigint = Sbigint_mul(bigint1, bigint2);
        if (!mul_bigint) return NULL;

        struct Sobj* mul_obj = Sobj_make_userdata(mul_bigint);
        mul_obj->meta = obj1->meta;
        return mul_obj;
    } else {
        fprintf(stderr, "Error: At least one operand must be a big integer for multiplication.\n");
        return NULL;
    }
}

struct Sobj* Sobj_div_bigint(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type == USER_DATA_OBJ && obj2->type != USER_DATA_OBJ) {
        char* buffer = float_to_string(obj2->value->value);
        struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
        struct Sbigint* bigint2 = Sbigint_new(buffer);
        bigint2->digits[0] = (char)(obj2->value->value + '0');
        bigint2->length = 1;
        struct Sbigint* div_bigint = Sbigint_div(bigint1, bigint2);
        Sbigint_free(bigint2);
        if (!div_bigint) return NULL;
        struct Sobj* div_obj = Sobj_make_userdata(div_bigint);
        div_obj->meta = obj1->meta;
        return div_obj;
    } else if (obj1->type != USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        char* buffer = float_to_string(obj1->value->value);
        struct Sbigint* bigint1 = Sbigint_new(buffer);
        bigint1->digits[0] = (char)(obj1->value->value + '0');
        bigint1->length = 1;
        struct Sbigint* div_bigint = Sbigint_div(bigint1, obj2->f_type->f_userdata->data);
        Sbigint_free(bigint1);
        if (!div_bigint) return NULL;
        struct Sobj* div_obj = Sobj_make_userdata(div_bigint);
        div_obj->meta = obj2->meta;
        return div_obj;
    } else if (obj1->type == USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
        struct Sbigint* bigint2 = obj2->f_type->f_userdata->data;

        struct Sbigint* div_bigint = Sbigint_div(bigint1, bigint2);
        if (!div_bigint) return NULL;

        struct Sobj* div_obj = Sobj_make_userdata(div_bigint);
        div_obj->meta = obj2->meta;
        return div_obj;
    } else {
        fprintf(stderr, "Error: At least one operand must be a big integer for division.\n");
        return NULL;
    }
}

struct Sobj* Sobj_bigint_bigger(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type != USER_DATA_OBJ || obj2->type != USER_DATA_OBJ) {
        fprintf(stderr, "Error: Both operands must be big integers for comparison.\n");
        return NULL;
    }
    struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
    struct Sbigint* bigint2 = obj2->f_type->f_userdata->data;
    return Sobj_make_bool(Sbigint_bigger(bigint1, bigint2));
}

struct Sobj* Sobj_bigint_bigger_equal(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type != USER_DATA_OBJ || obj2->type != USER_DATA_OBJ) {
        fprintf(stderr, "Error: Both operands must be big integers for comparison.\n");
        return NULL;
    }
    struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
    struct Sbigint* bigint2 = obj2->f_type->f_userdata->data;
    return Sobj_make_bool(Sbigint_bigger_equal(bigint1, bigint2));
}

struct Sobj* Sobj_bigint_smaller(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type != USER_DATA_OBJ || obj2->type != USER_DATA_OBJ) {
        fprintf(stderr, "Error: Both operands must be big integers for comparison.\n");
        return NULL;
    }
    struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
    struct Sbigint* bigint2 = obj2->f_type->f_userdata->data;
    return Sobj_make_bool(Sbigint_smaller(bigint1, bigint2));
}

struct Sobj* Sobj_bigint_smaller_equal(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type != USER_DATA_OBJ || obj2->type != USER_DATA_OBJ) {
        fprintf(stderr, "Error: Both operands must be big integers for comparison.\n");
        return NULL;
    }
    struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
    struct Sbigint* bigint2 = obj2->f_type->f_userdata->data;
    return Sobj_make_bool(Sbigint_smaller_equal(bigint1, bigint2));
}

struct Sobj* Sobj_bigint_equal(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type != USER_DATA_OBJ || obj2->type != USER_DATA_OBJ) {
        fprintf(stderr, "Error: Both operands must be big integers for comparison.\n");
        return NULL;
    }
    struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
    struct Sbigint* bigint2 = obj2->f_type->f_userdata->data;
    return Sobj_make_bool(Sbigint_equal(bigint1, bigint2));
}

struct Sobj* Sobj_bigint_not_equal(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type != USER_DATA_OBJ || obj2->type != USER_DATA_OBJ) {
        fprintf(stderr, "Error: Both operands must be big integers for comparison.\n");
        return NULL;
    }
    struct Sbigint* bigint1 = obj1->f_type->f_userdata->data;
    struct Sbigint* bigint2 = obj2->f_type->f_userdata->data;
    return Sobj_make_bool(Sbigint_not_equal(bigint1, bigint2));
}

struct Sobj* Sobj_make_bigint(struct Sframe* frame) {
    struct Sobj* str_obj = Sframe_pop(frame);
    
    if (str_obj->type != STRING_OBJ) {
        fprintf(stderr, "Error: Expected a string to create a big integer.\n");
        return NULL;
    }

    struct Sbigint* bigint = Sbigint_new(str_obj->f_type->f_str->string);
    struct Sobj* bigint_obj = Sobj_make_userdata(bigint);

    bigint_obj->meta = Smeta_new();

    bigint_obj->meta->mm_add = Sobj_add_bigint;
    bigint_obj->meta->mm_sub = Sobj_sub_bigint;
    bigint_obj->meta->mm_mul = Sobj_mul_bigint;
    bigint_obj->meta->mm_div = Sobj_div_bigint;
    bigint_obj->meta->mm_tostring = Sobj_print_bigint;

    bigint_obj->meta->mm_eq = Sobj_bigint_equal;
    bigint_obj->meta->mm_ne = Sobj_bigint_not_equal;
    bigint_obj->meta->mm_gt = Sobj_bigint_bigger;
    bigint_obj->meta->mm_lt = Sobj_bigint_smaller;
    bigint_obj->meta->mm_ge = Sobj_bigint_bigger_equal;
    bigint_obj->meta->mm_le = Sobj_bigint_smaller_equal;

    bigint_obj->meta->mm_free = Sobj_free_bigint;

    return bigint_obj;
}

// =============== End of Big Integer Functions =================

SUNY_API struct Sframe* Smain(struct Sframe* frame, struct Scompiler* compiler) {
    SunyInitialize_variable(frame, compiler, 30, "pi", NUMBER_OBJ, Sobj_set_int(PI));
    SunyInitialize_variable(frame, compiler, 31, "e", NUMBER_OBJ, Sobj_set_int(E));
 
    SunyInitialize_c_api_func(frame, compiler, 33, "vector", 1, Sobj_make_vector);
    SunyInitialize_c_api_func(frame, compiler, 38, "complex", 2, Sobj_make_complex);
    SunyInitialize_c_api_func(frame, compiler, 39, "bigint", 1, Sobj_make_bigint);

    SunyInitialize_c_api_func(frame, compiler, 34, "cos", 1, Scos);
    SunyInitialize_c_api_func(frame, compiler, 35, "sin", 1, Ssin);
    SunyInitialize_c_api_func(frame, compiler, 36, "tan", 1, Stan);
    SunyInitialize_c_api_func(frame, compiler, 37, "cot", 1, Scot);
    
    return frame;
}