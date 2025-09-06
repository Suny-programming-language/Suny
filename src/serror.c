#include "serror.h"

int break_loop() {
    while (1) {}
    return 0;
}

struct Serror *
Serror_new(void) {
    struct Serror *error = malloc(sizeof(struct Serror));

    error->type = NULL;
    error->message = NULL;

    error->line = 0;
    error->column = 0;

    error->lexer = Slexer_new();

    return error;
}

struct Serror *
Serror_set(char *type, char *message, struct Slexer *lexer) {
    struct Serror *error = Serror_new();

    error->type = type;
    error->message = message;

    error->line = lexer->line;
    error->column = lexer->column;

    error->lexer = lexer;

    return error;
}

int
Serror_syntax_error
(struct Serror *error) {
    printf("%s: %s\n", error->type, error->message);
    printf("At file '%s', line %d\n", error->lexer->file->file, error->lexer->line);

    break_loop();

    return 0;
}

int
Serror_print
(struct Serror *error) {
    printf("Error: %s\n", error->message);

    break_loop();

    return 0;
}

int
Serror_free
(struct Serror *error) {
    error->type = NULL;
    error->message = NULL;

    error->line = 0;
    error->column = 0;
    
    free(error);
    
    Slexer_free(error->lexer);

    return 0;
}

int
Serror_runtime_error
(char *message, struct Slexer *lexer) {
    printf("RuntimeError: %s\n", message);
    printf("At line %d, column %d\n", lexer->line, lexer->column);

    break_loop();

    return 0;
}

int
Serror_compile_error
(char *message, struct Slexer *lexer) {
    printf("CompileError: %s\n", message);
    printf("At file '%s', line %d\n", lexer->file->file, lexer->line);

    break_loop();

    return 0;
}

int
Serror_unknown_error
(char *message, struct Slexer *lexer) {
    printf("UnknownError: %s\n", message);
    printf("At file '%s', line %d\n", lexer->file->file, lexer->line);

    break_loop();

    return 0;
}

int
Sast_expected_expression(struct Sast *sast) {
    Sast_set_line(sast->lexer, sast);

    if (!sast) {
        struct Serror *error = Serror_set("SYNTAX_ERROR", "Expected expression", sast->lexer);
        Serror_syntax_error(error);
        return 0;
    };

    if (!is_expr(sast)) {
        struct Serror *error = Serror_set("SYNTAX_ERROR", "Expected expression", sast->lexer);
        Serror_syntax_error(error);
        return 0;
    }
}

int 
Serror_parser
(char *message, struct Slexer *lexer) {
    struct Serror *error = Serror_set("SYNTAX_ERROR", message, lexer);
    Serror_syntax_error(error);
    return 0;
}
