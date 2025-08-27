#ifndef STOOL_H
#define STOOL_H

#include "suny.h"

double 
Satof(const char *str);

int 
Stoi(const char *str);

void
Sreverse(void **array, int size);

char* 
Sto_char(char chr[], int len);

char*
Sftchr(float value);

char
Sgchrfromf(float value, int index);

#endif