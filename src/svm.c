#include "svm.h"

byte_t
get_next_code
(struct Sframe *frame) {
    if (frame->f_code_index >= frame->f_code->size) {
        printf("Error: end of code reached (code index: %d >= code size: %d)\n", 
            frame->f_code_index, frame->f_code->size);
        return 0;
    };

    return frame->f_code->code[frame->f_code_index++];
}

struct Sframe *
Svm_run_program(struct Sframe *frame) {
    struct Scode *code = frame->f_code;

    byte_t op = get_next_code(frame);
    int done = 0;
    
    if (op == PROGRAM_START) {
        while (!done) {
            op = get_next_code(frame);

            switch (op) {
                case PUSH_FLOAT: {
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
                    break;
                }

                case POP_TOP: {
                    struct Sobj *obj = POP_OBJ();
                    break;
                }

                case BINARY_ADD: {
                    struct Sobj *obj = POP_OBJ();
                    struct Sobj *obj2 = POP_OBJ();

                    float value = obj->value->value + obj2->value->value;
                    struct Sobj *obj3 = Sobj_set_int(value);
                    PUSH_OBJ(obj3);
                    break;
                }

                case BINARY_SUB: {
                    struct Sobj *obj = POP_OBJ();
                    struct Sobj *obj2 = POP_OBJ();

                    float value = obj->value->value - obj2->value->value;
                    struct Sobj *obj3 = Sobj_set_int(value);
                    PUSH_OBJ(obj3);
                    break;
                }

                case BINARY_MUL: {
                    struct Sobj *obj = POP_OBJ();
                    struct Sobj *obj2 = POP_OBJ();

                    float value = obj->value->value * obj2->value->value;
                    struct Sobj *obj3 = Sobj_set_int(value);
                    PUSH_OBJ(obj3);
                    break;
                }

                case BINARY_DIV: {
                    struct Sobj *obj = POP_OBJ();
                    struct Sobj *obj2 = POP_OBJ();

                    float value = obj->value->value / obj2->value->value;
                    struct Sobj *obj3 = Sobj_set_int(value);
                    PUSH_OBJ(obj3);
                    break;
                }

                case STORE_GLOBAL: {
                    struct Sobj *obj = POP_OBJ();
                    
                    int address = get_next_code(frame);
                    Sframe_store_global(frame, address, obj);

                    break;
                }

                case LOAD_GLOBAL: {
                    int address = get_next_code(frame);
                    struct Sobj *obj = Sframe_load_global(frame, address);
                    PUSH_OBJ(obj->f_value);
                    break;
                }

                case PRINT: {
                    struct Sobj *obj = POP_OBJ();
                    printf("%f\n", obj->value->value);
                    break;
                }

                case PROGRAM_END: {
                    done = 1;
                    break;
                }
            }
        }
    } else {
        printf("Error: invalid header, expected program start\n");
        return NULL;
    }

    return frame;
}