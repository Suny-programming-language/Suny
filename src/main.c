#include <stdio.h>
#include <string.h>

#include "svm.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: suny [file].suny\n");
        return 1;
    }

    char* file_name = argv[1];

    char* dot = strrchr(file_name, '.');
    if (!dot) {
        printf("No file extension found\n");
        return 1;
    }

    char* ext = dot + 1;

    if (strcmp(ext, "suny") != 0) {
        printf("Invalid file extension\n");
        return 1;
    }

    char* buff = Sbuff_read_file(file_name)->buffer;

    struct Sframe *frame = Sframe_new();
    
    struct Slexer *lexer = Slexer_init(buff);
    struct Sparser *parser = Sparser_init(lexer);
    struct Sast *ast = Sparser_parse_program(parser);

    struct Scompiler *compiler = Scompiler_new();
    struct Scode *code = Scompile_program(ast, compiler);
    struct Sc_api_func *api_func = Sc_api_func_set(Sprintf, "printf", 20);
    
    Sinitialize_c_api_func(frame, compiler, api_func);

    frame = Sframe_init(frame, code);
    frame = Svm_run_program(frame);

    return 0;
}