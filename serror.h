#ifndef SERROR_H
#define SERROR_H

#include <stdio.h>
#include <stdlib.h>

#include "slexer.h"
#include "sast.h"

struct Sast;

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

struct Serror *Serror_set_line
(char* type, char* message, int line, int column);

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

int
Sast_expected_expression
(struct Sast *sast);

int 
Serror_parser
(char *message, struct Slexer *lexer);

int
Serror_fatal_error  
(char *message, ...);

#endif