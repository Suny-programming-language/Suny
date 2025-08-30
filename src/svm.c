#include "svm.h"

char* print_op(char c) {
    switch (c) {
        case PUSH_FLOAT: return "PUSH_FLOAT";
        case BINARY_ADD: return "BINARY_ADD";
        case BINARY_SUB: return "BINARY_SUB";
        case BINARY_MUL: return "BINARY_MUL";
        case BINARY_DIV: return "BINARY_DIV";
        case PRINT: return "PRINT";
        case POP_TOP: return "POP_TOP";
        case LOAD_GLOBAL: return "LOAD_GLOBAL";
        case STORE_GLOBAL: return "STORE_GLOBAL";
        case PROGRAM_START: return "PROGRAM_START";
        case PROGRAM_END: return "PROGRAM_END";
        case BINARY_BIGGER: return "BINARY_BIGGER";
        case BINARY_SMALLER: return "BINARY_SMALLER";
        case BINARY_EQUAL: return "BINARY_EQUAL";
        case BINARY_BIGGER_EQUAL: return "BINARY_BIGGER_EQUAL";
        case BINARY_SMALLER_EQUAL: return "BINARY_SMALLER_EQUAL";
        case BINARY_NOT_EQUAL: return "BINARY_NOT_EQUAL";
        case MAKE_FUNCTION: return "MAKE_FUNCTION";
        case END_FUNCTION: return "END_FUNCTION";
        case FUNCTION_CALL: return "FUNCTION_CALL";
        case RETURN_TOP: return "RETURN_TOP";
    }
}

byte_t
get_next_code
(struct Sframe *frame) {
    return frame->f_code->code[frame->f_code_index++];
}

byte_t
jump_to(struct Sframe *frame, int address) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *jump_to(struct Sframe *frame, int address) (building...)\n");
#endif
    struct Spos pos = Slabel_map_get(frame->f_label_map, address);
    int index = pos.indexof;
    frame->f_code_index = index - 1;

#ifdef DEBUG
    printf("[svm.c] struct Sframe *jump_to(struct Sframe *frame, int address) (done)\n");
#endif

    return frame->f_code->code[frame->f_code_index];
}

struct Sframe *
Svm_run_program(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_run_program(struct Sframe *frame) (building...)\n");
#endif
    struct Scode *code = frame->f_code;

    byte_t op = get_next_code(frame);
    int done = 0;
    
    if (op == PROGRAM_START) {
        while (!done) {
            if (op == PROGRAM_END) {
                done = 1;
            } 

            else if (op == ADD_LABEL) {
                op = get_next_code(frame);
            }

            else if (op == PUSH_FLOAT) {
                frame = Svm_evalutate_PUSH_FLOAT(frame);
            }

            else if (op == LOAD_GLOBAL) {
                frame = Svm_evalutate_LOAD_GLOBAL(frame);
            }

            else if (op == STORE_GLOBAL) {
                frame = Svm_evalutate_STORE_GLOBAL(frame);
            }

            else if (op == MAKE_FUNCTION) {
                frame = Svm_evaluate_MAKE_FUNCTION(frame);
            }

            else if (op == PUSH_STRING) {
                frame = Svm_evaluate_PUSH_STRING(frame);
            }

            else if (op == BUILD_LIST) {
                frame = Svm_evaluate_BUILD_LIST(frame);
            }

            else if (op == LEN_OF) {
                frame = Svm_evaluate_LEN_OF(frame);
            }

            else if (op == POP_JUMP_IF_FALSE) {
                frame = Svm_evaluate_POP_JUMP_IF_FALSE(frame);
            }

            else if (op == FUNCTION_CALL) {
                frame = Svm_evaluate_FUNCTION_CALL(frame);
            }

            else if (op == JUMP_TO) {
                frame = Svm_evaluate_JUMP_TO(frame);
            }

            else if (IS_BINARY_OPER(op)) {
                frame = Svm_evalutate_BINARY_OPER(frame, op);
            }

            else if (op == LOAD_ITEM) {
                frame = Svm_evaluate_LOAD_ITEM(frame);
            }

            else if (op == STORE_ITEM) {
                frame = Svm_evaluate_STORE_ITEM(frame);
            }

            else if (op == PRINT) {
                frame = Svm_evaluate_PRINT(frame);
            }

            op = get_next_code(frame);
        }
    } else {
        printf("Invalid program %s\n", print_op(op));
    }

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_run_program(struct Sframe *frame) (done...)\n");
#endif

    return frame;
}

struct Sframe *
Svm_run_call_context(struct Scall_context *context) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_run_call_context(struct Scall_context *context) (building...)\n");
#endif
    struct Sframe *f_frame = context->frame;

    byte_t op = get_next_code(f_frame);

    context->ret_obj = Sobj_set_int(0);

    int done = 0;

    while (!done) {
        if (op == END_FUNCTION) {
            done = 1;
        }

        else if (IS_BINARY_OPER(op)) {
            f_frame = Svm_evalutate_BINARY_OPER(f_frame, op);
        }

        else if (op == PRINT) {
            f_frame = Svm_evaluate_PRINT(f_frame);
        }

        else if (op == RETURN_TOP) {
            struct Sobj *obj = Sframe_pop(f_frame);
            context->ret_obj = obj;
            done = 1;
        }

        else if (op == PUSH_FLOAT) {
            f_frame = Svm_evalutate_PUSH_FLOAT(f_frame);
        }

        else if (op == LOAD_GLOBAL) {
            f_frame = Svm_evalutate_LOAD_GLOBAL(f_frame);
        }

        else if (op == FUNCTION_CALL) {
            f_frame = Svm_evaluate_FUNCTION_CALL(f_frame);
        }

        else if (op == PUSH_STRING) {
            f_frame = Svm_evaluate_PUSH_STRING(f_frame);
        }

        else if (op == STORE_GLOBAL) {
            f_frame = Svm_evalutate_STORE_GLOBAL(f_frame);
        }

        op = get_next_code(f_frame);
    }

    Sframe_push(context->main_frame, context->ret_obj);

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_run_call_context(struct Scall_context *context) (done)\n");
#endif

    return context->main_frame;
}

struct Sframe *
Svm_evaluate_MAKE_FUNCTION
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_MAKE_FUNCTION(struct Sframe *frame) (building...)\n");
#endif
    address_t address = get_next_code(frame);
    byte_t args_count = get_next_code(frame);
    int code_size = 0;

    struct Scode *code = Scode_new();

    byte_t op = get_next_code(frame);

    while (op != END_FUNCTION) {
        PUSH(code, op);
        op = get_next_code(frame);
        ++code_size;
    }

    PUSH(code, END_FUNCTION);

    struct Sfunc *func = Sfunc_set(code, args_count, code_size);

    func->args_size = args_count;

    struct Sobj *f_obj = Sobj_set_func(func);

    Sfunc_ready(func, args_count);
    Sframe_store_global(frame, address, f_obj,  FUNC_OBJ);

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_MAKE_FUNCTION(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe *
Svm_evaluate_FUNCTION_CALL
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_FUNCTION_CALL(struct Sframe *frame) (building...)\n");
#endif

    struct Sobj **f_local = malloc(sizeof(struct Sobj*) * MAX_ARGS_SIZE);

    struct Sobj *f_obj = POP_OBJ();

    if (f_obj->type == BUILTIN_OBJ) {
        struct Sobj* (*func)(struct Sframe*) =
            (struct Sobj* (*)(struct Sframe*)) load_c_api_func(f_obj);

        func(frame);

        return frame;
    }

    struct Scall_context *context = Scall_context_new();
    struct Sframe *f_frame = context->frame;

    context->main_frame = frame;
    context->ret_obj = Sobj_set_int(0);
    Scall_context_set_func(context, f_obj->f_type->f_func);

    int address = 0;

    for (int i = 0; i < f_obj->f_type->f_func->args_size; ++i) {
        struct Sobj* value = Sframe_pop(frame);

        Sframe_store_global(f_frame, address++, value, LOCAL_OBJ);
    }

    Svm_run_call_context(context);

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_FUNCTION_CALL(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe *
Svm_evalutate_PUSH_FLOAT
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evalutate_PUSH_FLOAT(struct Sframe *frame) (building...)\n");
#endif

    byte_t b1 = get_next_code(frame);
    byte_t b2 = get_next_code(frame);
    byte_t b3 = get_next_code(frame);
    byte_t b4 = get_next_code(frame);

    uint32_t i = (uint32_t)b1 |
                ((uint32_t)b2 << 8) |
                ((uint32_t)b3 << 16) |
                ((uint32_t)b4 << 24);

    float value;
    memcpy(&value, &i, sizeof(value));

    struct Sobj *obj = Sobj_set_int(value);

    PUSH_OBJ(obj);

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evalutate_PUSH_FLOAT(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe *
Svm_evalutate_LOAD_GLOBAL
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evalutate_LOAD_GLOBAL(struct Sframe *frame) (building...)\n");
#endif
    int address = get_next_code(frame);
    struct Sobj *obj = Sframe_load_global(frame, address);

    PUSH_OBJ(obj->f_value);
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evalutate_LOAD_GLOBAL(struct Sframe *frame) (done)\n");
#endif
    return frame;
}

struct Sframe *
Svm_evalutate_STORE_GLOBAL
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evalutate_STORE_GLOBAL(struct Sframe *frame) (building...)\n");
#endif

struct Sobj *obj = POP_OBJ();
    
    int address = get_next_code(frame);
    Sframe_store_global(frame, address, obj, GLOBAL_OBJ);

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evalutate_STORE_GLOBAL(struct Sframe *frame) (done)\n");
#endif
    return frame;
}

struct Sframe *
Svm_evalutate_BINARY_OPER
(struct Sframe *frame, byte_t op) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evalutate_BINARY_OPER(struct Sframe *frame, byte_t op) (building...)\n");
#endif
    struct Sobj *obj2 = POP_OBJ();
    struct Sobj *obj1 = POP_OBJ();

    float value1 = obj1->value->value;
    float value2 = obj2->value->value;

    struct Sobj *obj = Sobj_set_int(0);

    switch (op) {
        case BINARY_ADD: {
            obj = Seval_add(obj1, obj2);
            break;
        } case BINARY_SUB: {
            obj = Seval_sub(obj1, obj2);
            break;
        } case BINARY_MUL: {
            obj = Seval_mul(obj1, obj2);
            break;
        } case BINARY_DIV: {
            obj = Seval_div(obj1, obj2);
            break;
        } case BINARY_BIGGER : {
            obj = Seval_bigger(obj1, obj2);
            break;
        } case BINARY_SMALLER : {
            obj = Seval_smaller(obj1, obj2);
            break;
        } case BINARY_EQUAL : {
            obj = Seval_equal(obj1, obj2);
            break;
        } case BINARY_NOT_EQUAL : {
            obj = Seval_not_equal(obj1, obj2);
            break;
        } case BINARY_BIGGER_EQUAL : {
            obj = Seval_bigger_and_equal(obj1, obj2);
            break;
        } case BINARY_SMALLER_EQUAL : {
            obj = Seval_smaller_and_equal(obj1, obj2);
            break;
        } default: {
            break;
        }
    }

    Sframe_push(frame, obj);
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evalutate_BINARY_OPER(struct Sframe *frame, byte_t op) (done)\n");
#endif
    return frame;
}


struct Sframe *
Svm_evaluate_PRINT
(struct Sframe *frame) {
    struct Sobj *obj = POP_OBJ();
    float val = obj->value->value;
    if (val != 0 && (fabs(val) < 0.01 || fabs(val) >= 10000))
        printf("%.2e\n", val);
    else
        printf("%.5f\n", val);
    return frame;
}

struct Sframe *
Svm_evaluate_PUSH_STRING
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_PUSH_STRING(struct Sframe *frame) (building...)\n");
#endif

    int size = get_next_code(frame);

    char* buff = malloc(size + 1);

    for (int i = 0; i < size; ++i) {
        buff[i] = get_next_code(frame);
    }

    buff[size] = '\0';

    struct Sobj *obj = Sobj_make_str(buff, size);

    PUSH_OBJ(obj);

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_PUSH_STRING(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe *
Svm_evaluate_POP_JUMP_IF_FALSE
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_POP_JUMP_IF_FALSE(struct Sframe *frame) (building...)\n");
#endif
    int address = get_next_code(frame);

    struct Sobj *obj = Sframe_pop(frame);

    if (!obj->value->value) {
        jump_to(frame, address);
        return frame;
    }

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_POP_JUMP_IF_FALSE(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe *
Svm_evaluate_JUMP_TO
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_POP_JUMP_IF_FALSE(struct Sframe *frame) (building...)\n");
#endif

    int address = get_next_code(frame);
    jump_to(frame, address);

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_POP_JUMP_IF_FALSE(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe *
Svm_evaluate_BUILD_LIST
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_BUILD_LIST(struct Sframe *frame) (building...)\n");
#endif

    int size = get_next_code(frame);

    struct Slist *list = Slist_new();

    for (int i = 0; i < size; ++i) {
        struct Sobj *item = Sframe_pop(frame);
        Slist_add(list, item);
    };

    struct Sobj *obj = Sobj_make_list(list);

    PUSH_OBJ(obj);

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_BUILD_LIST(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe *
Svm_evaluate_LOAD_ITEM
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_LOAD_ITEM(struct Sframe *frame) (building...)\n");
#endif

    struct Sobj *index = Sframe_pop(frame);
    struct Sobj *list = Sframe_pop(frame);

    if (list->type == LIST_OBJ) {
        if (index->value->value >= list->f_type->f_list->count) {
            Sframe_push(frame, Sobj_set_int(0));
            return frame;
        };

        struct Sobj *item = Slist_get(list->f_type->f_list, index->value->value);
        Sframe_push(frame, item);
    } else {
        Sframe_push(frame, Sobj_set_int(0));
    }
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_LOAD_ITEM(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe *
Svm_evaluate_STORE_ITEM
(struct Sframe *frame) {
    struct Sobj *value = Sframe_pop(frame);
    struct Sobj *index = Sframe_pop(frame);
    struct Sobj *list = Sframe_pop(frame);

    int index_value = index->value->value;

    list->f_type->f_list->array[index_value] = value;

    return frame;
}

struct Sframe *
Svm_evaluate_LEN_OF
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_LEN_OF(struct Sframe *frame) (building...)\n");
#endif
    struct Sobj *list = Sframe_pop(frame);

    Sframe_push(frame, Sobj_set_int(list->f_type->f_list->count));

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_LEN_OF(struct Sframe *frame) (done)\n");
#endif

    return frame;
}