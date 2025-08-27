#include "svm.h"

byte_t
get_next_code
(struct Sframe *frame) {
    return frame->f_code->code[frame->f_code_index++];
}

struct Sframe *
Svm_run_program(struct Sframe *frame) {
    struct Scode *code = frame->f_code;

    byte_t op = get_next_code(frame);
    int done = 0;
    
    if (op == PROGRAM_START) {
        while (!done) {
            if (op == PROGRAM_END) {
                done = 1;
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

            else if (op == FUNCTION_CALL) {
                frame = Svm_evaluate_FUNCTION_CALL(frame);
            }

            else if (IS_BINARY_OPER(op)) {
                frame = Svm_evalutate_BINARY_OPER(frame, op);
            }

            else if (op == PRINT) {
                frame = Svm_evaluate_PRINT(frame);
            }

            op = get_next_code(frame);
        }
    } else {
        printf("Error: invalid header, expected program start\n");
        return NULL;
    }

    return frame;
}

struct Sframe *
Svm_run_call_context(struct Scall_context *context) {
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

        else if (op == STORE_GLOBAL) {
            f_frame = Svm_evalutate_STORE_GLOBAL(f_frame);
        }

        op = get_next_code(f_frame);
    }

    Sframe_push(context->main_frame, context->ret_obj);

    return context->main_frame;
}

struct Sframe *
Svm_evaluate_MAKE_FUNCTION
(struct Sframe *frame) {
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

    return frame;
}

struct Sframe *
Svm_evaluate_FUNCTION_CALL
(struct Sframe *frame) {
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

    return frame;
}

struct Sframe *
Svm_evalutate_PUSH_FLOAT
(struct Sframe *frame) {
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

    return frame;
}

struct Sframe *
Svm_evalutate_LOAD_GLOBAL
(struct Sframe *frame) {
    int address = get_next_code(frame);
    struct Sobj *obj = Sframe_load_global(frame, address);

    PUSH_OBJ(obj->f_value);

    return frame;
}

struct Sframe *
Svm_evalutate_STORE_GLOBAL
(struct Sframe *frame) {
    struct Sobj *obj = POP_OBJ();
    
    int address = get_next_code(frame);
    Sframe_store_global(frame, address, obj, GLOBAL_OBJ);

    return frame;
}

struct Sframe *
Svm_evalutate_BINARY_OPER
(struct Sframe *frame, byte_t op) {
    struct Sobj *obj2 = POP_OBJ();
    struct Sobj *obj1 = POP_OBJ();

    float value2 = obj2->value->value;
    float value1 = obj1->value->value;

    struct Sobj *obj = Sobj_set_int(0);

    switch (op) {
        case BINARY_ADD: obj->value->value = value1 + value2; break;
        case BINARY_SUB: obj->value->value = value1- value2; break;
        case BINARY_MUL: obj->value->value = value1 * value2; break;
        case BINARY_DIV: obj->value->value = value1 / value2; break;
        case BINARY_BIGGER_EQUAL: obj->value->value = value1 >= value2; break;
        case BINARY_BIGGER: obj->value->value = value1 > value2; break;
        case BINARY_SMALLER_EQUAL: obj->value->value = value1 <= value2; break;
        case BINARY_SMALLER: obj->value->value = value1 < value2; break;
        case BINARY_EQUAL: obj->value->value = value1 == value2; break;
        case BINARY_NOT_EQUAL: obj->value->value = value1 != value2; break;
    }

    PUSH_OBJ(obj);

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