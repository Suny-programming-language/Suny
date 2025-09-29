#include "seval.h"

int Slist_cmp(struct Slist *list1, struct Slist *list2) {
    int min = list1->count < list2->count ? list1->count : list2->count;

    for (int i = 0; i < min; i++) {
        struct Sobj *item1 = list1->array[i];
        struct Sobj *item2 = list2->array[i];

        struct Sobj *eq = Seval_equal(item1, item2);
        if (!eq->value->value) {
            struct Sobj *gt = Seval_bigger(item1, item2);
            if (gt->value->value) return 1;   
            else return -1;                 
        }
    }

    if (list1->count == list2->count) return 0;
    return (list1->count > list2->count) ? 1 : -1;
}

struct Sobj *
Seval_add
(struct Sobj *obj1, struct Sobj *obj2) {
#ifdef DEBUG
    printf("[seval.c] struct Sobj *Seval_add(struct Sobj *obj1, struct Sobj *obj2) (pass)\n");
#endif
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        struct Sstr *str = Sstr_add(str1, str2);

        struct Sobj *sobj = Sobj_make_str_obj(str);
        
        return sobj;
    } else if (obj1->type == LIST_OBJ && obj2->type == LIST_OBJ) {
        struct Slist *list1 = obj1->f_type->f_list;
        struct Slist *list2 = obj2->f_type->f_list;

        struct Slist *list = Slist_append(list1, list2);

        struct Sobj *sobj = Sobj_make_list(list);
        
        return sobj;
    } else if (obj1->type == USER_DATA_OBJ) {
        if (obj1->meta && obj1->meta->mm_add) {
            return obj1->meta->mm_add(obj1, obj2);
        } else {
            return null_obj;
        }
    } else if (obj2->type == USER_DATA_OBJ) {
        if (obj2->meta && obj2->meta->mm_add) {
            return obj2->meta->mm_add(obj1, obj2);
        } else {
            return null_obj;
        }
    }
    else {
        return Sobj_set_int(obj1->value->value + obj2->value->value);
    }
}

struct Sobj *
Seval_sub
(struct Sobj *obj1, struct Sobj *obj2) {
#ifdef DEBUG
    printf("[seval.c] struct Sobj *Seval_sub(struct Sobj *obj1, struct Sobj *obj2) (pass)\n");
#endif

    if (obj1->type == USER_DATA_OBJ) {
        if (obj1->meta && obj1->meta->mm_sub) {
            return obj1->meta->mm_sub(obj1, obj2);
        } else {
            return null_obj;
        }
    } else if (obj2->type == USER_DATA_OBJ) {
        if (obj2->meta && obj2->meta->mm_sub) {
            return obj2->meta->mm_sub(obj1, obj2);
        } else {
            return null_obj;
        }
    }

    return Sobj_set_int(obj1->value->value - obj2->value->value);
}

struct Sobj *
Seval_mul
(struct Sobj *obj1, struct Sobj *obj2) {
#ifdef DEBUG
    printf("[seval.c] struct Sobj *Seval_mul(struct Sobj *obj1, struct Sobj *obj2) (pass)\n");
#endif
    if (obj1->type == STRING_OBJ) {
        struct Sstr *str = obj1->f_type->f_str;
        struct Sstr *sstr = Sstr_mul(str, obj2->value->value);

        struct Sobj *sobj = Sobj_make_str_obj(sstr);
        
        return sobj;
    } else if (obj2->type == STRING_OBJ) {
        struct Sstr *str = obj2->f_type->f_str;
        struct Sstr *sstr = Sstr_mul(str, obj1->value->value);

        struct Sobj *sobj = Sobj_make_str_obj(sstr);
        
        return sobj;
    } else if (obj1->type == LIST_OBJ) {
        struct Slist *list = obj1->f_type->f_list;
        struct Slist *slist = Slist_mul(list, obj2->value->value);

        struct Sobj *sobj = Sobj_make_list(slist);
        
        return sobj;
    } else if (obj2->type == LIST_OBJ) {
        struct Slist *list = obj2->f_type->f_list;
        struct Slist *slist = Slist_mul(list, obj1->value->value);

        struct Sobj *sobj = Sobj_make_list(slist);
        
        return sobj;
    } else if (obj1->type == USER_DATA_OBJ) {
        if (obj1->meta && obj1->meta->mm_mul) {
            return obj1->meta->mm_mul(obj1, obj2);
        } else {
            return null_obj;
        }
    } else if (obj2->type == USER_DATA_OBJ) {
        if (obj2->meta && obj2->meta->mm_mul) {
            return obj2->meta->mm_mul(obj1, obj2);
        } else {
            return null_obj;
        }
    } else {
        return Sobj_set_int(obj1->value->value * obj2->value->value);
    }
}

struct Sobj *
Seval_div
(struct Sobj *obj1, struct Sobj *obj2) {
#ifdef DEBUG
    printf("[seval.c] struct Sobj *Seval_div(struct Sobj *obj1, struct Sobj *obj2) (pass)\n");
#endif
    if (obj1->type == USER_DATA_OBJ) {
        if (obj1->meta && obj1->meta->mm_div) {
            return obj1->meta->mm_div(obj1, obj2);
        } else {
            return null_obj;
        }
    } else if (obj2->type == USER_DATA_OBJ) {
        if (obj2->meta && obj2->meta->mm_div) {
            return obj2->meta->mm_div(obj1, obj2);
        } else {
            return null_obj;
        }
    }

    return Sobj_set_int(obj1->value->value / obj2->value->value);
}

struct Sobj *
Seval_bigger
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        char* a = str1->string;
        char* b = str2->string;

        int size_a = str1->size;
        int size_b = str2->size;

        int result = Scharcmp_bigger(a, b, size_a, size_b);

        if (result) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    } else if (obj1->type == LIST_OBJ && obj2->type == LIST_OBJ) {
        int cmp = Slist_cmp(obj1->f_type->f_list, obj2->f_type->f_list);
        if (cmp > 0) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    } else if (obj1->type == USER_DATA_OBJ) {
        if (obj1->meta && obj1->meta->mm_gt) {
            return obj1->meta->mm_gt(obj1, obj2);
        } else {
            return null_obj;
        }
    } else if (obj2->type == USER_DATA_OBJ) {
        if (obj2->meta && obj2->meta->mm_gt) {
            return obj2->meta->mm_gt(obj1, obj2);
        } else {
            return null_obj;
        }
    } else {
        if (obj1->value->value > obj2->value->value) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    }
}

struct Sobj *
Seval_smaller
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        char* a = str1->string;
        char* b = str2->string;

        int size_a = str1->size;
        int size_b = str2->size;

        int result = Scharcmp_smaller(a, b, size_a, size_b);

        if (result) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    } else if (obj1->type == LIST_OBJ && obj2->type == LIST_OBJ) {
        int cmp = Slist_cmp(obj1->f_type->f_list, obj2->f_type->f_list);
        if (cmp < 0) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    } else if (obj1->type == USER_DATA_OBJ) {
        if (obj1->meta && obj1->meta->mm_lt) {
            return obj1->meta->mm_lt(obj1, obj2);
        } else {
            return null_obj;
        }
    } else if (obj2->type == USER_DATA_OBJ) {
        if (obj2->meta && obj2->meta->mm_lt) {
            return obj2->meta->mm_lt(obj1, obj2);
        } else {
            return null_obj;
        }
    } else {
        if (obj1->value->value < obj2->value->value) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    }
}

struct Sobj *
Seval_equal
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        char* a = str1->string;
        char* b = str2->string;

        int size_a = str1->size;
        int size_b = str2->size;

        int result = Scharcmp_equal(a, b, size_a, size_b);

        if (result) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    } else if (obj1->type == LIST_OBJ && obj2->type == LIST_OBJ) {
        int cmp = Slist_cmp(obj1->f_type->f_list, obj2->f_type->f_list);
        if (cmp == 0) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    } else if (obj1->type == USER_DATA_OBJ) {
        if (obj1->meta && obj1->meta->mm_eq) {
            return obj1->meta->mm_eq(obj1, obj2);
        } else {
            return null_obj;
        }
    } else if (obj2->type == USER_DATA_OBJ) {
        if (obj2->meta && obj2->meta->mm_eq) {
            return obj2->meta->mm_eq(obj1, obj2);
        } else {
            return null_obj;
        }
    } else {
        if (obj1->value->value == obj2->value->value) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    }
}

struct Sobj *
Seval_not_equal
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        char* a = str1->string;
        char* b = str2->string;

        int size_a = str1->size;
        int size_b = str2->size;

        int result = Scharcmp_equal(a, b, size_a, size_b);

        if (!result) {
            return Sobj_make_true();   
        } else {
            return Sobj_make_false();
        }
    } else if (obj1->type == LIST_OBJ && obj2->type == LIST_OBJ) {
        int cmp = Slist_cmp(obj1->f_type->f_list, obj2->f_type->f_list);
        if (cmp != 0) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    } else if (obj1->type == USER_DATA_OBJ) {
        if (obj1->meta && obj1->meta->mm_ne) {
            return obj1->meta->mm_ne(obj1, obj2);
        } else {
            return null_obj;
        }
    } else if (obj2->type == USER_DATA_OBJ) {
        if (obj2->meta && obj2->meta->mm_ne) {
            return obj2->meta->mm_ne(obj1, obj2);
        } else {
            return null_obj;
        }
    } else {
        if (obj1->value->value != obj2->value->value) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    }
}

struct Sobj *
Seval_bigger_and_equal
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        char* a = str1->string;
        char* b = str2->string;

        int size_a = str1->size;
        int size_b = str2->size;

        int result = Scharcmp_bigger(a, b, size_a, size_b);
        int result2 = Scharcmp_equal(a, b, size_a, size_b);

        if (result || result2) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    } else if (obj1->type == LIST_OBJ && obj2->type == LIST_OBJ) {
        int cmp = Slist_cmp(obj1->f_type->f_list, obj2->f_type->f_list);
        if (cmp > 0 || cmp == 0) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    } else if (obj1->type == USER_DATA_OBJ) {
        if (obj1->meta && obj1->meta->mm_ge) {
            return obj1->meta->mm_ge(obj1, obj2);
        } else {
            return null_obj;
        }
    } else if (obj2->type == USER_DATA_OBJ) {
        if (obj2->meta && obj2->meta->mm_ge) {
            return obj2->meta->mm_ge(obj1, obj2);
        } else {
            return null_obj;
        }
    } else {
        if (obj1->value->value > obj2->value->value || obj1->value->value == obj2->value->value) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    }
}

struct Sobj *
Seval_smaller_and_equal
(struct Sobj *obj1, struct Sobj *obj2) {
    if (obj1->type == STRING_OBJ && obj2->type == STRING_OBJ) {
        struct Sstr *str1 = obj1->f_type->f_str;
        struct Sstr *str2 = obj2->f_type->f_str;

        char* a = str1->string;
        char* b = str2->string;

        int size_a = str1->size;
        int size_b = str2->size;

        int result = Scharcmp_smaller(a, b, size_a, size_b);
        int result2 = Scharcmp_equal(a, b, size_a, size_b);

        if (result || result2) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    } else if (obj1->type == LIST_OBJ && obj2->type == LIST_OBJ) {
        int cmp = Slist_cmp(obj1->f_type->f_list, obj2->f_type->f_list);
        if (cmp < 0 || cmp == 0) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    } else if (obj1->type == USER_DATA_OBJ) {
        if (obj1->meta && obj1->meta->mm_le) {
            return obj1->meta->mm_le(obj1, obj2);
        } else {
            return null_obj;
        }
    } else if (obj2->type == USER_DATA_OBJ) {
        if (obj2->meta && obj2->meta->mm_le) {
            return obj2->meta->mm_le(obj1, obj2);
        } else {
            return null_obj;
        }
    } else {
        if (obj1->value->value < obj2->value->value || obj1->value->value == obj2->value->value) {
            return Sobj_make_true();
        } else {
            return Sobj_make_false();
        }
    }
}