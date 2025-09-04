#include "Suny.h"

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

struct Sframe* SunyRunSimpleString(char* str) {
    struct SZIO* zio = Sbuff_read_file(str);

    struct Slexer *lexer = Slexer_init(zio->buffer);
    lexer->file = zio;

    struct Sparser *parser = Sparser_init(lexer);
    struct Sast *ast = Sparser_parse_program(parser);

    struct Scompiler *compiler = Scompiler_new();

    struct Sframe *frame = Sframe_new();
    SunyInstallLib(frame, compiler);

    struct Scode *code = Scompile_program(ast, compiler);

    frame = Sframe_init(frame, code);

    frame = Svm_run_program(frame);

    return frame;
}

struct Sframe* SunyRunFile(char* file) {
    struct SZIO* zio = Sbuff_read_file(file);

    struct Slexer *lexer = Slexer_init(zio->buffer);
    lexer->file = zio;

    struct Sparser *parser = Sparser_init(lexer);
    struct Sast *ast = Sparser_parse_program(parser);

    struct Scompiler *compiler = Scompiler_new();

    struct Sframe *frame = Sframe_new();
    SunyInstallLib(frame, compiler);

    struct Scode *code = Scompile_program(ast, compiler);

    frame = Sframe_init(frame, code);
    frame = Svm_run_program(frame);

    return frame;
}

struct Scode* SunyCompileFile(char* file) {
    struct SZIO* zio = Sbuff_read_file(file);

    struct Slexer *lexer = Slexer_init(zio->buffer);
    lexer->file = zio;

    struct Sparser *parser = Sparser_init(lexer);
    struct Sast *ast = Sparser_parse_program(parser);

    struct Scompiler *compiler = Scompiler_new();

    struct Sframe *frame = Sframe_new();
    SunyInstallLib(frame, compiler);

    struct Scode *code = Scompile_program(ast, compiler);

    return code;
}