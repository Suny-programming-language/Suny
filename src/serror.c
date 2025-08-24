#include "serror.h"

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

struct Serror *
Serror_syntax_error
(struct Serror *error) {
    printf("SyntaxError: %s\n", error->message);
    printf("At line %d, column %d\n", error->line, error->column);
}

void
Serror_print
(struct Serror *error) {
    printf("Error: %s\n", error->message);
}

void
Serror_free
(struct Serror *error) {
    error->type = NULL;
    error->message = NULL;

    error->line = 0;
    error->column = 0;
    
    free(error);
    
    Slexer_free(error->lexer);
}

struct Serror *
Serror_runtime_error
(char *message, struct Slexer *lexer) {
    printf("RuntimeError: %s\n", message);
    printf("At line %d, column %d\n", lexer->line, lexer->column);
}

struct Serror *
Serror_compile_error
(char *message, struct Slexer *lexer) {
    printf("CompileError: %s\n", message);
    printf("At line %d, column %d\n", lexer->line, lexer->column);
}

struct Serror *
Serror_unknown_error
(char *message, struct Slexer *lexer) {
    printf("UnknownError: %s\n", message);
    printf("At line %d, column %d\n", lexer->line, lexer->column);
}   