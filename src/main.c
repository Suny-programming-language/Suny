#include "svm.h"

int main(int argc, char** argv) {
    char* file_name = argv[1];

    char* buff = Sbuff_read_file(file_name)->buffer;
    
    struct Slexer *lexer = Slexer_init(buff);
    struct Sparser *parser = Sparser_init(lexer);
    struct Sast *ast = Sparser_parse_program(parser);
    struct Scompiler *compiler = Scompiler_new();
    struct Scode *code = Scompile_program(ast, compiler);
    struct Sframe *frame = Sframe_init(code);

    frame = Svm_run_program(frame);

    return 0;
}