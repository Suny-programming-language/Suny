#include "sstr.h"

struct Sstr *Sstr_new(void) {
    struct Sstr *str = malloc(sizeof(struct Sstr));
    str->size = 0;
    str->string = NULL;
    return str;
}

struct Sstr *Sstr_new_from_char(char *chr, int size) {
    struct Sstr *str = malloc(sizeof(struct Sstr));

    str->size = size;
    str->string = chr;

    return str;
}

void Sstr_free(struct Sstr *str) {
    free(str);
    str = NULL;
}

struct Sstr *Sstr_add(struct Sstr *str1, struct Sstr *str2) {
    struct Sstr *str = Sstr_new();

    str->string = malloc(sizeof(char) * (str1->size + str2->size + 1));

    for (int i = 0; i < str1->size; i++) {
        str->string[i] = str1->string[i];
    }

    for (int i = 0; i < str2->size; i++) {
        str->string[i + str1->size] = str2->string[i];
    }

    str->size = str1->size + str2->size;

    return str;
}

struct Sstr *Sstr_mul(struct Sstr *str, int n) {
    struct Sstr *result = Sstr_new();

    result->string = malloc(sizeof(char) * (str->size * n + 1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < str->size; j++) {
            result->string[i * str->size + j] = str->string[j];
        }
    }

    result->size = str->size * n;

    return result;
}

struct Sobj *Sobj_make_str(char* str, int size) {
    struct Sstr *sstr = Sstr_new_from_char(str, size);
    struct Sobj *sobj = Sobj_new();

    sobj->type = STRING_OBJ;
    sobj->f_type = Stype_new();
    sobj->f_type->f_str = sstr;

    return sobj;
}