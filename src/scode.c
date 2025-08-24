#include "scode.h"

struct Scode *
Scode_new(void) {
    struct Scode *code = malloc(sizeof(struct Scode));

    code->size = 0;
    
    return code;
}

int 
Scode_free
(struct Scode *code) {
    free(code);
    return 0;
}

int 
Scode_add
(struct Scode *code, unsigned char c) {
    code->code[code->size++] = c;

    if (code->size > MAX_CODE_SIZE) {
        printf("Error: code size limit exceeded (max size: %d < current size: %d)\n", 
            MAX_CODE_SIZE, code->size);
        return -1;
    }

    return 0;
}

int
Scode_push
(struct Scode *scode, struct Scode *code) {
    for (int i = 0; i < code->size; i++) {
        Scode_add(scode, code->code[i]);
    }

    return 0;
}   

int
Scode_print
(struct Scode *code) {
    for (int i = 0; i < code->size; i++) {
        unsigned char c = code->code[i];

        switch(c) {
            case PUSH_FLOAT:
                printf("PUSH_FLOAT ");

                float result = 0.0;

                unsigned char c1 = code->code[i + 1];
                unsigned char c2 = code->code[i + 2];
                unsigned char c3 = code->code[i + 3];
                unsigned char c4 = code->code[i + 4];

                unsigned char float_code[4] = {c1, c2, c3, c4};

                memcpy(&result, float_code, sizeof(float_code));

                printf("%f\n", result);

                i += 4;

                break;
            case BINARY_ADD:
                printf("BINARY_ADD\n");
                break;
            case BINARY_SUB:
                printf("BINARY_SUB\n");
                break;
            case BINARY_MUL:
                printf("BINARY_MUL\n");
                break;
            case BINARY_DIV:
                printf("BINARY_DIV\n");
                break;

            case STORE_GLOBAL:
                printf("STORE_GLOBAL ");

                unsigned char address = code->code[i + 1];

                printf("%d\n", address);

                i += 1;
                break;
            case PROGRAM_START:
                printf("PROGRAM_START\n");
                break;
            case PROGRAM_END:
                printf("PROGRAM_END\n");
                break;
            default:
                printf("%d\n", c);
                break;
        }
    }
}