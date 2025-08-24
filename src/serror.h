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

struct Serror *
Serror_new(void);

struct Serror *
Serror_set(char *type, char *message, struct Slexer *lexer);

struct Serror *
Serror_syntax_error
(struct Serror *error);

void
Serror_print
(struct Serror *error);

void
Serror_free
(struct Serror *error);

struct Serror *
Serror_runtime_error
(char *message, struct Slexer *lexer);

struct Serror *
Serror_compile_error
(char *message, struct Slexer *lexer);

struct Serror *
Serror_unknown_error
(char *message, struct Slexer *lexer);

#endif