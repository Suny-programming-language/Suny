#include <stdio.h>
#include <string.h>

#include "svm.h"

int prompt() {
    printf("Suny 1.0 Copyright (C) 2025-present, by dinhsonhai132\n");

    struct Sframe *frame = Sframe_new();
    struct Scompiler *compiler = Scompiler_new();

    SunyInstallLib(frame, compiler);

    char buff[1024];
    for (;;) {
        printf(">> ");
        if (!fgets(buff, sizeof(buff), stdin)) break;
        
        if (strlen(buff) == 0) continue;

        struct Slexer *lexer = Slexer_init(buff);
        struct Sparser *parser = Sparser_init(lexer);
        struct Sast *ast = Sparser_parse_program(parser);
        
        struct Scode *code = Scompile_program(ast, compiler);

        frame = Sframe_init(frame, code);
        frame = Svm_run_program(frame);
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        prompt();
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

    SunyInstallLib(frame, compiler);

    struct Scode *code = Scompile_program(ast, compiler);
    
    frame = Sframe_init(frame, code);
    frame = Svm_run_program(frame);

    return 0;
}