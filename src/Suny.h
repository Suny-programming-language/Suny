#ifndef SUNY
#define SUNY

#include "svm.h"
#include "score.h"

#define same_string(a, b) (strcmp(a, b) == 0)

#define compilefile(file) Scode_print(SunyCompileFile((file)))

struct Sframe* SunyRunSimpleString(char* str);

struct Sframe* SunyRunFile(char* file);

struct Scode* SunyCompileFile(char* file);

int prompt(void);

#endif