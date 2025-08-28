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

    char* buff = Sbuff_read_file(file_name)->buffer;

    struct Sframe *frame = Sframe_new();
    
    struct Slexer *lexer = Slexer_init(buff);
    struct Sparser *parser = Sparser_init(lexer);
    struct Sast *ast = Sparser_parse_program(parser);

    struct Scompiler *compiler = Scompiler_new();

    SunyInstallLib(frame, compiler);

    struct Scode *code = Scompile_program(ast, compiler);
    
    frame = Sframe_init(frame, code);

    // struct Slabel_map* label_map = frame->f_label_map;

    // for (int i = 0; i < label_map->label_count; i++) {
    //     struct Spos pos = label_map->label[i];
    //     printf("label: %d %d\n", pos.address, pos.indexof);
    // }

    // Scode_print(code);

    frame = Svm_run_program(frame);

    return 0;
}