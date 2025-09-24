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
        case PUSH_STRING: return "PUSH_STRING";
        case PUSH_TRUE: return "PUSH_TRUE";
        case PUSH_FALSE: return "PUSH_FALSE";
        case POP_JUMP_IF_TRUE: return "POP_JUMP_IF_TRUE";
        case POP_JUMP_IF_FALSE: return "POP_JUMP_IF_FALSE";
        case JUMP_TO: return "JUMP_TO";
        case ADD_LABEL: return "ADD_LABEL";
        case JUMP_FORWARD: return "JUMP_FORWARD";
        case JUMP_BACKWARD: return "JUMP_BACKWARD";
        case SKIP_TO_INDEX: return "SKIP_TO_INDEX";
        case EXIT_PROGRAM: return "EXIT_PROGRAM";
        case STOP_PROGRAM: return "STOP_PROGRAM";
        case LOAD_ITEM: return "LOAD_ITEM";
        case STORE_ITEM: return "STORE_ITEM";
        case BUILD_LIST: return "BUILD_LIST";
        case LEN_OF: return "LEN_OF";
        case LOAD_TRUE: return "LOAD_TRUE";
        case LOAD_FALSE: return "LOAD_FALSE";
        case CLASS_BEGIN: return "CLASS_BEGIN";
        case CLASS_END: return "CLASS_END";
        case AND_LOG: return "AND_LOG";
        case OR_LOG: return "OR_LOG";
        case NOT_LOG: return "NOT_LOG";
        case SKIP: return "SKIP";
        case LOAD_ATTR: return "LOAD_ATTR";
        case STORE_ATTR: return "STORE_ATTR";
        case LOAD_METHOD: return "LOAD_METHOD";
        default: return "UNKNOWN_OP";
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

    frame->gc_pool = Sgc_new_pool();
    
    Sgc_activate(frame);

    byte_t op = get_next_code(frame);
    int done = 0;
    
    if (op == PROGRAM_START) {
        op = get_next_code(frame);
        
        while (!done) {
            if (op == PROGRAM_END) {
                done = 1;
            }

            else if (op == AND_LOG) {
                frame = Svm_evaluate_AND_LOG(frame);
            }

            else if (op == OR_LOG) {
                frame = Svm_evaluate_OR_LOG(frame);
            }

            else if (op == NOT_LOG) {
                frame = Svm_evaluate_NOT_LOG(frame);
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

            else if (op == LOAD_ATTR) {
                frame = Svm_evaluate_LOAD_ATTR(frame);
            }

            else if (op == MAKE_FUNCTION) {
                frame = Svm_evaluate_MAKE_FUNCTION(frame);
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

            else if (op == STORE_ATTR) {
                frame = Svm_evaluate_STORE_ATTR(frame);
            }

            else if (op == CLASS_BEGIN) {
                frame = Svm_evaluate_CLASS_BEGIN(frame);
            }

            else if (op == POP_TOP) {
                #ifdef DEBUG
                    printf("[svm.c] struct Sframe *Svm_run_program(struct Sframe *frame) (POP_TOP)\n");
                #endif
                struct Sobj *obj = Sframe_pop(frame);
                Sgc_dec_ref(obj, frame->gc_pool);
                #ifdef DEBUG
                    printf("[svm.c] struct Sframe *Svm_run_program(struct Sframe *frame) (done)\n");
                #endif
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

            else if (op == LOAD_TRUE) {
                frame = Svm_evaluate_LOAD_TRUE(frame);
            }

            else if (op == LOAD_FALSE) {
                frame = Svm_evaluate_LOAD_FALSE(frame);
            } else {
                printf("Invalid program %s\n", print_op(op));
                done = 1;
            }

            op = get_next_code(frame);
            
            if (frame->gc_pool->pool_index > POOL_SIZE_LIMIT) {
                Sgc_collect(frame->gc_pool);
            }
        }
    } else {
        printf("Invalid program %s\n", print_op(op));
    }

    Sgc_deactivate(frame);   

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

    context->ret_obj = null_obj;

    Sgc_activate(f_frame);

    int done = 0;

    while (!done) {
        if (op == END_FUNCTION) {
            done = 1;
        }
        
        else if (op == ADD_LABEL) {
            op = get_next_code(f_frame);
        }

        else if (op == POP_TOP) {
            #ifdef DEBUG
                printf("[svm.c] struct Sframe *Svm_run_call_context(struct Scall_context *context) (POP_TOP)\n");
            #endif
            struct Sobj *obj = Sframe_pop(f_frame);
            Sgc_dec_ref(obj, f_frame->gc_pool);
            #ifdef DEBUG
                printf("[svm.c] struct Sframe *Svm_run_call_context(struct Scall_context *context) (done)\n");
            #endif
        }

        else if (op == AND_LOG) {
            f_frame = Svm_evaluate_AND_LOG(f_frame);
        }

        else if (op == OR_LOG) {
            f_frame = Svm_evaluate_OR_LOG(f_frame);
        }

        else if (op == NOT_LOG) {
            f_frame = Svm_evaluate_NOT_LOG(f_frame);
        }

        else if (IS_BINARY_OPER(op)) {
            f_frame = Svm_evalutate_BINARY_OPER(f_frame, op);
        }

        else if (op == PRINT) {
            f_frame = Svm_evaluate_PRINT(f_frame);
        }

        else if (op == RETURN_TOP) {
            struct Sobj *obj = Sframe_pop(f_frame);

            Sobj_free(context->ret_obj);
            context->ret_obj = obj; 
            break;
        }

        else if (op == PUSH_FLOAT) {
            f_frame = Svm_evalutate_PUSH_FLOAT(f_frame);
        }

        else if (op == LOAD_ATTR) {
            f_frame = Svm_evaluate_LOAD_ATTR(f_frame);
        }

        else if (op == STORE_ATTR) {
            f_frame = Svm_evaluate_STORE_ATTR(f_frame);
        }

        else if (op == CLASS_BEGIN) {
            f_frame = Svm_evaluate_CLASS_BEGIN(f_frame);
        }

        else if (op == MAKE_FUNCTION) {
            f_frame = Scall_context_make_inner_function(context);
        }

        else if (op == LOAD_GLOBAL) {
            f_frame = Svm_evaluate_LOAD_LOCAL(f_frame);
        }

        else if (op == FUNCTION_CALL) {
            f_frame = Svm_evaluate_FUNCTION_CALL(f_frame);
        }

        else if (op == PUSH_STRING) {
            f_frame = Svm_evaluate_PUSH_STRING(f_frame);
        }

        else if (op == STORE_GLOBAL) {
            f_frame = Svm_evaluate_STORE_LOCAL(f_frame);
        }

        else if (op == JUMP_TO) {
            f_frame = Svm_evaluate_JUMP_TO(f_frame);
        }

        else if (op == POP_JUMP_IF_FALSE) {
            f_frame = Svm_evaluate_POP_JUMP_IF_FALSE(f_frame);
        }

        else if (op == BUILD_LIST) {
            f_frame = Svm_evaluate_BUILD_LIST(f_frame);
        }

        else if (op == LEN_OF) {
            f_frame = Svm_evaluate_LEN_OF(f_frame);
        }

        else if (op == LOAD_ITEM) {
            f_frame = Svm_evaluate_LOAD_ITEM(f_frame);
        }

        else if (op == STORE_ITEM) {
            f_frame = Svm_evaluate_STORE_ITEM(f_frame);
        }

        else if (op == LOAD_TRUE) {
            f_frame = Svm_evaluate_LOAD_TRUE(f_frame);
        }

        else if (op == LOAD_FALSE) {
            f_frame = Svm_evaluate_LOAD_FALSE(f_frame);
        }

        if (f_frame->gc_pool->pool_index > POOL_SIZE_LIMIT) {
            Sgc_collect(f_frame->gc_pool);
        }

        op = get_next_code(f_frame);
    }

    Sgc_deactivate(f_frame);

    Sframe_push(context->main_frame, context->ret_obj);

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_run_call_context(struct Scall_context *context) (done)\n");
#endif

    return context->main_frame;
}

struct Sframe*
Scall_context_make_inner_function
(struct Scall_context *context) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Scall_context_make_inner_function(struct Scall_context *context) (building...)\n");
#endif

    struct Sframe *f_frame = context->frame;

    byte_t fargs_count = get_next_code(f_frame);

    int code_size = 0;

    struct Scode *code = Scode_new();

    byte_t op = get_next_code(f_frame); 

    int func_level = 1;

    while (1) {
        if (op == MAKE_FUNCTION) {
            func_level++;
        }
        
        if (op == END_FUNCTION) {
            func_level--;
        } else if (op == MAKE_FUNCTION) {
            func_level++;
        }

        if (op == END_FUNCTION && func_level == 0) break;

        PUSH(code, op);

        ++code_size;

        op = get_next_code(f_frame);
    }

    PUSH(code, END_FUNCTION);

    struct Sfunc *func = Sfunc_set(code, fargs_count, code_size);

    func->args_size = fargs_count;

    func->frame = f_frame;

    struct Sobj *f_obj = Sobj_set_func(func);

    Sfunc_ready(func, fargs_count);

    Sframe_push(f_frame, f_obj);
    
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Scall_context_make_inner_function(struct Scall_context *context) (done)\n");
#endif

    return f_frame;
}

struct Sframe *
Svm_evaluate_MAKE_FUNCTION
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_MAKE_FUNCTION(struct Sframe *frame) (building...)\n");
#endif
    byte_t args_count = get_next_code(frame);

    int code_size = 0;

    struct Scode *code = Scode_new();

    int func_level = 1;

    byte_t op = get_next_code(frame);

    while (1) {
        if (op == MAKE_FUNCTION) {
            func_level++;
        }
        
        if (op == END_FUNCTION) {
            func_level--;
        } else if (op == MAKE_FUNCTION) {
            func_level++;
        }

        if (op == END_FUNCTION && func_level == 0) break;

        PUSH(code, op);

        ++code_size;

        op = get_next_code(frame);
    }

    PUSH(code, END_FUNCTION);

    struct Sfunc *func = Sfunc_set(code, args_count, code_size);

    func->args_size = args_count;

    struct Sobj *f_obj = Sobj_set_func(func);

    Sframe_push(frame, f_obj);

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

    struct Sobj *f_obj = Sframe_pop(frame);

    if (f_obj->type == BUILTIN_OBJ) {
        struct Sobj* (*func)(struct Sframe*) = (struct Sobj* (*)(struct Sframe*)) load_c_api_func(f_obj);

        struct Sobj* result = func(frame);

        Sframe_push(frame, result);

        return frame;
    }

    if (f_obj->type == CLASS_OBJ) {
        struct Sclass *sclass = Sclass_copy(f_obj->f_type->f_class);

        struct Sobj* obj = Sobj_new();
        obj->type = CLASS_OBJ;
        obj->f_type = Stype_new();
        obj->f_type->f_class = sclass;
        
        Sframe_push(frame, obj);

        return frame;
    }

    struct Scall_context *context = Scall_context_new();
    context->main_frame = frame;

    struct Sframe *f_frame = context->frame;
    struct Scode *f_code = f_obj->f_type->f_func->code;

    f_frame->f_globals = frame->f_globals;
    f_frame->f_globals_size = frame->f_globals_size;
    f_frame->f_globals_index = frame->f_globals_index;
    f_frame->gc_pool = Sgc_new_pool();
    f_frame->f_code = f_code;
    f_frame->f_code_index = 0;
    f_frame->f_label_map = Slabel_map_set_program(f_code);

    int address = 0;

    for (int i = 0; i < f_obj->f_type->f_func->args_size; ++i) {
        struct Sobj* value = Sframe_pop(frame);
        Sframe_store_local(f_frame, address++, value, LOCAL_OBJ);
    }

    Svm_run_call_context(context);

    Scall_context_free(context);

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

    Sframe_push(frame, obj->f_value);
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

    struct Sobj *obj = Sframe_pop(frame);
    
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
    struct Sobj *obj2 = Sframe_pop(frame);
    struct Sobj *obj1 = Sframe_pop(frame);

    float value1 = obj1->value->value;
    float value2 = obj2->value->value;

    struct Sobj *obj = NULL;

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

    Sgc_dec_ref(obj1, frame->gc_pool);
    Sgc_dec_ref(obj2, frame->gc_pool);

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
    printf("%g\n", val);
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

    Sgc_dec_ref(obj, frame->gc_pool);

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
        inc_ref(item);
        Slist_add(list, item);
    };

    struct Sobj *obj = Sobj_make_list(list);

    Sframe_push(frame, obj);

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
        if (index->value->value > list->f_type->f_list->count) {
            printf("Error: index out of range\n");
            SUNY_BREAK_POINT;
            return frame;
        };

        struct Sobj *item = Slist_get(list->f_type->f_list, index->value->value);

        if (!item) {
            printf("Error: index out of range\n");
            SUNY_BREAK_POINT;
        }
        
        Sframe_push(frame, item);
    } else if (list->type == STRING_OBJ) {
        if (index->value->value > list->f_type->f_str->size) {
            printf("Error: index out of range\n");
            SUNY_BREAK_POINT;
            return frame;
        };

        int index_value = index->value->value;
        char c = list->f_type->f_str->string[index_value];
        struct Sobj *obj = Sobj_make_char(c);

        if (!obj) {
            printf("Error: index out of range\n");
            SUNY_BREAK_POINT;
        }

        Sframe_push(frame, obj);
    } else if (list->type == USER_DATA_OBJ) {
        struct Sobj *ret = NULL;
        if (list->meta && list->meta->mm_index) {
            ret = list->meta->mm_index(list, index);
            Sframe_push(frame, ret);
        } else {
            printf("Error: user data index not supported\n");
            SUNY_BREAK_POINT;
        }
    } else {
        Sframe_push(frame, Sobj_set_int(0));
    }
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_LOAD_ITEM(struct Sframe *frame) (done)\n");
#endif

    Sgc_dec_ref(list, frame->gc_pool);
    Sgc_dec_ref(index, frame->gc_pool);

    return frame;
}

struct Sframe *
Svm_evaluate_STORE_ITEM
(struct Sframe *frame) {
    struct Sobj *value = Sframe_pop(frame);
    struct Sobj *index = Sframe_pop(frame);
    struct Sobj *list = Sframe_pop(frame);

    int index_value = index->value->value;

    struct Sobj *pre_item = list->f_type->f_list->array[index_value];

    list->f_type->f_list->array[index_value] = value;

    dec_ref(pre_item);
    dec_ref(index);

    Sgc_dec_ref(pre_item, frame->gc_pool);
    Sgc_dec_ref(index, frame->gc_pool);

    inc_ref(value);

    return frame;
}

struct Sframe *
Svm_evaluate_LEN_OF
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_LEN_OF(struct Sframe *frame) (building...)\n");
#endif
    struct Sobj *list = Sframe_pop(frame);

    Sgc_dec_ref(list, frame->gc_pool);

    if (list->type == LIST_OBJ) {
        struct Sobj *obj = Sobj_set_int(list->f_type->f_list->count);
        Sframe_push(frame, obj);
    } else if (list->type == STRING_OBJ) {
        struct Sobj *obj = Sobj_set_int(list->f_type->f_str->size);
        Sframe_push(frame, obj);
    }

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_LEN_OF(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe *
Svm_evaluate_LOAD_TRUE
(struct Sframe *frame) {
    struct Sobj *obj = Sobj_set_int(1);
    obj->type = TRUE_OBJ;
    PUSH_OBJ(obj);
    return frame;
}

struct Sframe *
Svm_evaluate_LOAD_FALSE
(struct Sframe *frame) {
    struct Sobj *obj = Sobj_set_int(0);
    obj->type = FALSE_OBJ;
    PUSH_OBJ(obj);
    return frame;
}

struct Sframe *
Svm_evaluate_LOAD_LOCAL
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_LOAD_LOCAL(struct Sframe *frame) (building...)\n");
#endif

    int address = get_next_code(frame);
    struct Sobj *obj = Sframe_load_local(frame, address);

    PUSH_OBJ(obj->f_value);

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_LOAD_LOCAL(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe *
Svm_evaluate_STORE_LOCAL
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_STORE_LOCAL(struct Sframe *frame) (building...)\n");
#endif
    
    struct Sobj *obj = Sframe_pop(frame);
    int address = get_next_code(frame);

    Sframe_store_local(frame, address, obj, LOCAL_OBJ);

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_STORE_LOCAL(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe *
Svm_evaluate_CLASS_BEGIN
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_CLASS_BEGIN(struct Sframe *frame) (building...)\n");
#endif

    byte_t op = get_next_code(frame);

    struct Sclass *sclass = Sclass_new();

    struct Sobj *self_obj = Sobj_new();
    self_obj->type = CLASS_OBJ;
    self_obj->f_type = Stype_new();
    self_obj->f_type->f_class = sclass;

    sclass = Sclass_store_member(sclass, frame, self_obj, 0);

    while (op != CLASS_END) {
        if (op == ADD_LABEL) {
            op = get_next_code(frame);
        }

        else if (op == AND_LOG) {
            frame = Svm_evaluate_AND_LOG(frame);
        }

        else if (op == OR_LOG) {
            frame = Svm_evaluate_OR_LOG(frame);
        }

        else if (op == NOT_LOG) {
            frame = Svm_evaluate_NOT_LOG(frame);
        }

        else if (op == PUSH_FLOAT) {
            frame = Svm_evalutate_PUSH_FLOAT(frame);
        }

        else if (op == LOAD_GLOBAL) {
            frame = Svm_evalutate_LOAD_GLOBAL(frame);
        }

        else if (op == STORE_GLOBAL) {
#ifdef DEBUG
            printf("[svm.c] struct Sframe *Svm_evaluate_STORE_GLOBAL(struct Sframe *frame) (building...)\n");
#endif
            int address = get_next_code(frame);
            sclass = Sclass_store_object(sclass, frame, address);
        
#ifdef DEBUG
            printf("[svm.c] struct Sframe *Svm_evaluate_STORE_GLOBAL(struct Sframe *frame) (done)\n");
#endif
        }

        else if (op == CLASS_BEGIN) {
            frame = Svm_evaluate_CLASS_BEGIN(frame);
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

        else if (op == MAKE_FUNCTION) {
            frame = Svm_evaluate_MAKE_FUNCTION(frame);
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

        else if (op == POP_TOP) {
            struct Sobj *obj = Sframe_pop(frame);
            Sgc_dec_ref(obj, frame->gc_pool);
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

        else if (op == LOAD_TRUE) {
            frame = Svm_evaluate_LOAD_TRUE(frame);
        }

        else if (op == LOAD_FALSE) {
            frame = Svm_evaluate_LOAD_FALSE(frame);
        }

        op = get_next_code(frame);
    }

    struct Sobj *obj = Sobj_make_class(sclass);

    Sframe_push(frame, obj);

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_CLASS_BEGIN(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe*
Svm_evaluate_NOT_LOG
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_NOT_LOG(struct Sframe *frame) (building...)\n");
#endif    
    struct Sobj *obj = Sframe_pop(frame);

    Sgc_dec_ref(obj, frame->gc_pool);

    int value = !obj->value->value;

    if (value) {
        Sframe_push(frame, Sobj_make_true());
    } else {
        Sframe_push(frame, Sobj_make_false());
    }

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_NOT_LOG(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe*
Svm_evaluate_AND_LOG
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_AND_LOG(struct Sframe *frame) (building...)\n");
#endif

    struct Sobj *obj1 = Sframe_pop(frame);
    struct Sobj *obj2 = Sframe_pop(frame);

    Sgc_dec_ref(obj1, frame->gc_pool);
    Sgc_dec_ref(obj2, frame->gc_pool);

    int value = obj1->value->value && obj2->value->value;

    if (value) {
        Sframe_push(frame, Sobj_make_true());
    } else {
        Sframe_push(frame, Sobj_make_false());
    }

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_AND_LOG(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe*
Svm_evaluate_OR_LOG
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_OR_LOG(struct Sframe *frame) (building...)\n");
#endif
    struct Sobj *obj1 = Sframe_pop(frame);
    struct Sobj *obj2 = Sframe_pop(frame);

    Sgc_dec_ref(obj1, frame->gc_pool);
    Sgc_dec_ref(obj2, frame->gc_pool);

    int value = obj1->value->value || obj2->value->value;

    if (value) {
        Sframe_push(frame, Sobj_make_true());
    } else {
        Sframe_push(frame, Sobj_make_false());
    }

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_OR_LOG(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe*
Svm_evaluate_LOAD_ATTR
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_LOAD_ATTR(struct Sframe *frame) (building...)\n");
#endif

    int address = get_next_code(frame);

    struct Sobj* class = Sframe_pop(frame);

    if (class->type == CLASS_OBJ) {
        struct Sclass *sclass = class->f_type->f_class;

        struct Sobj* value = Sclass_get_object(sclass, address);

        if (value != NULL) {
            Sframe_push(frame, value->f_value);
        } else {
            Sframe_push(frame, Sobj_set_int(0));
        }
    }

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_LOAD_ATTR(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe*
Svm_evaluate_STORE_ATTR
(struct Sframe *frame) {
#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_STORE_ATTR(struct Sframe *frame) (building...)\n");
#endif

    struct Sobj* class = Sframe_pop(frame);
    struct Sobj* value = Sframe_pop(frame);

    int address = get_next_code(frame);

    if (class->type == CLASS_OBJ) {
        struct Sclass *sclass = class->f_type->f_class;
        Sclass_store_member(sclass, frame, value, address);
    }

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_STORE_ATTR(struct Sframe *frame) (done)\n");
#endif

    return frame;
}

struct Sframe*
Svm_run_func(struct Sframe *frame, struct Sobj *f_obj) {
    if (f_obj->type == BUILTIN_OBJ) {
#ifdef DEBUG
        printf("[svm.c] struct Sframe *Svm_evaluate_FUNCTION_CALL(struct Sframe *frame) (builtin)\n");
#endif
        struct Sobj* (*func)(struct Sframe*) = (struct Sobj* (*)(struct Sframe*)) load_c_api_func(f_obj);

        struct Sobj* result = func(frame);

        Sframe_push(frame, result);

#ifdef DEBUG
        printf("[svm.c] struct Sframe *Svm_evaluate_FUNCTION_CALL(struct Sframe *frame) (done)\n");
#endif
        return frame;
    }

    if (f_obj->type == CLASS_OBJ) {
#ifdef DEBUG
        printf("[svm.c] struct Sframe *Svm_evaluate_FUNCTION_CALL(struct Sframe *frame) (class)\n");
#endif
        struct Sclass *sclass = Sclass_copy(f_obj->f_type->f_class);

        struct Sobj* obj = Sobj_new();
        obj->type = CLASS_OBJ;
        obj->f_type = Stype_new();
        obj->f_type->f_class = sclass;

        Sframe_push(frame, obj);

#ifdef DEBUG
        printf("[svm.c] struct Sframe *Svm_evaluate_FUNCTION_CALL(struct Sframe *frame) (class)\n");
#endif

        return frame;
    }

    #ifdef DEBUG
        printf("[svm.c] struct Sframe *Svm_evaluate_FUNCTION_CALL(struct Sframe *frame) (func)\n");
    #endif

    struct Scall_context *context = Scall_context_new();
    struct Sframe *f_frame = context->frame;

    f_frame->f_label_map = Slabel_map_set_program(f_obj->f_type->f_func->code);

    f_frame->f_globals = frame->f_globals;
    f_frame->f_globals_size = frame->f_globals_size;

    f_frame->f_locals = f_obj->f_type->f_func->frame->f_locals;
    f_frame->f_locals_size = f_obj->f_type->f_func->frame->f_locals_size;

    context->main_frame = frame;

    #ifdef DEBUG
        printf("[svm.c] struct Sframe *Svm_evaluate_FUNCTION_CALL(struct Sframe *frame) (context)\n");
    #endif

    Scall_context_set_func(context, f_obj->f_type->f_func);

    #ifdef DEBUG
        printf("[svm.c] struct Sframe *Svm_evaluate_FUNCTION_CALL(struct Sframe *frame) (args)\n");
    #endif

    int address = 0;

    for (int i = 0; i < f_obj->f_type->f_func->args_size; ++i) {
    #ifdef DEBUG
        printf("[svm.c] struct Sframe *Svm_evaluate_FUNCTION_CALL(struct Sframe *frame) (arg start %d)\n", i);
    #endif
        struct Sobj* value = Sframe_pop(frame);

        Sframe_store_local(f_frame, address++, value, LOCAL_OBJ);
    #ifdef DEBUG
        printf("[svm.c] struct Sframe *Svm_evaluate_FUNCTION_CALL(struct Sframe *frame) (arg end %d)\n", i);
    #endif
    }

    Svm_run_call_context(context);

    Scall_context_free(context);

    f_obj->f_type->f_func->call_context = context;

#ifdef DEBUG
    printf("[svm.c] struct Sframe *Svm_evaluate_FUNCTION_CALL(struct Sframe *frame) (done)\n");
#endif

    return frame;
}