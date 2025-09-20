#include "scode.h"

struct Scode *
Scode_new(void) {
    struct Scode *code = malloc(sizeof(struct Scode));

    code->size = 0;
    code->capacity = MAX_CODE_SIZE;
    
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
            case LOAD_ITEM:
                printf("LOAD_ITEM\n");
                break;
            case BINARY_ADD:
                printf("BINARY_ADD\n");
                break;
            case STORE_ITEM:
                printf("STORE_ITEM\n");
                break;
            case LEN_OF:
                printf("LEN_OF\n");
                break;
            case BINARY_SUB:
                printf("BINARY_SUB\n");
                break;
            case POP_JUMP_IF_TRUE: {
                printf("POP_JUMP_IF_TRUE ");

                unsigned char address = code->code[i + 1];

                printf("%d\n", address);

                i += 1;
                break;
            }

            case JUMP_TO: {
                printf("JUMP_TO ");

                unsigned char address = code->code[i + 1];

                printf("%d\n", address);
            }

            case POP_JUMP_IF_FALSE: {
                printf("POP_JUMP_IF_FALSE ");

                unsigned char address = code->code[i + 1];

                printf("%d\n", address);

                i += 1;
                break;
            }
            case ADD_LABEL: {
                printf("ADD_LABEL ");

                unsigned char address = code->code[i + 1];

                printf("%d\n", address);

                i += 1;
                break;
            }
            case BINARY_MUL:
                printf("BINARY_MUL\n");
                break;
            case BINARY_DIV:
                printf("BINARY_DIV\n");
                break;
            case LOAD_GLOBAL: {
                printf("LOAD_GLOBAL ");

                unsigned char address = code->code[i + 1];

                printf("%d\n", address);

                i += 1;
                break;
            }

            case BUILD_LIST: {
                printf("BUILD_LIST ");

                unsigned char count = code->code[i + 1];

                printf("%d\n", count);

                i += 1;
                break;
            }

            case PUSH_STRING: {
                printf("PUSH_STRING ");

                i += 1;

                int size = code->code[i];

                printf("%d \"", size);

                int pos = 0;
                while (pos < size) {
                    printf("%c", code->code[i + 1 + pos]);
                    pos++;
                }

                printf("\"\n");

                i += size;
                break;
            }

            case STORE_GLOBAL: {
                printf("STORE_GLOBAL ");

                unsigned char address = code->code[i + 1];

                printf("%d\n", address);

                i += 1;
                break;
            }

            case BINARY_BIGGER:
                printf("BINARY_BIGGER\n");
                break;
            case BINARY_SMALLER:
                printf("BINARY_SMALLER\n");
                break;
            case BINARY_EQUAL:
                printf("BINARY_EQUAL\n");
                break;
            case BINARY_NOT_EQUAL:
                printf("BINARY_NOT_EQUAL\n");
                break;
            case PRINT:
                printf("PRINT\n");
                break;
            case RETURN_TOP:
                printf("RETURN_TOP\n");
                break;
            case POP_TOP:
                printf("POP_TOP\n");
                break;
            case MAKE_FUNCTION: {
                printf("MAKE_FUNCTION ");

                unsigned char size = code->code[i + 2];

                printf("%d\n", size);

                i += 1;
                break;
            }

            case LOAD_ATTR: {
                printf("LOAD_ATTR ");

                unsigned char address = code->code[i + 1];

                printf("%d\n", address);

                i += 1;

                break;
            }

            case STORE_ATTR: {
                printf("STORE_ATTR ");

                unsigned char address = code->code[i + 1];

                printf("%d\n", address);

                i += 1;

                break;
            }

            case CLASS_BEGIN:
                printf("CLASS_BEGIN\n");
                break;

            case CLASS_END:
                printf("CLASS_END\n");
                break;

            case END_FUNCTION:
                printf("END_FUNCTION\n");
                break;

            case FUNCTION_CALL:
                printf("FUNCTION_CALL\n");
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

struct Scode *
Scode_get_code_from(char* file, struct Scompiler *compiler) {
    struct SZIO* zio = Sbuff_read_file(file);

    struct Slexer *lexer = Slexer_init(zio->buffer);
    lexer->file = zio;

    struct Sparser *parser = Sparser_init(lexer);
    struct Sast *ast = Sparser_parse_program(parser);

    SunyScopeInitializeCompiler(compiler);

    struct Scode *code = Scode_new();
    
    for (int i = 0; i < ast->child_count; i++) {
        struct Scode *child = Scompile(ast->children[i], compiler);
        INSERT(code, child);

        if (is_expr(ast->children[i])) {
            PUSH(code, POP_TOP);
        }
    }

    return code;
}

struct Scode *
Scode_insert_to_top(struct Scode *code, struct Scode *insert) {
    struct Scode *new_code = Scode_new();

    for (int i = 0; i < insert->size; i++) {
        Scode_add(new_code, insert->code[i]);
    }

    for (int i = 0; i < code->size; i++) {
        Scode_add(new_code, code->code[i]);
    }

    return new_code;
}