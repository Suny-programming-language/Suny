#ifndef SUNY
#define SUNY

#include "svm.h"
#include "score.h"

struct Sframe* SunyRunSimpleString(char* str);

struct Sframe* SunyRunFile(char* file);

int prompt(void);

#endif