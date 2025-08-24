#ifndef SERROR_H
#define SERROR_H

#include <stdio.h>

#include "slexer.h"

struct Serror {
    char* type;
    char* message;
  
    int line;
    int column;

    struct Slexer *lexer;
};

int break_loop();

struct Serror *
Serror_new(void);

struct Serror *
Serror_set(char *type, char *message, struct Slexer *lexer);

int
Serror_syntax_error
(struct Serror *error);

int
Serror_print
(struct Serror *error);

int
Serror_free
(struct Serror *error);

int
Serror_runtime_error
(char *message, struct Slexer *lexer);

int
Serror_compile_error
(char *message, struct Slexer *lexer);

int
Serror_unknown_error
(char *message, struct Slexer *lexer);

#endif