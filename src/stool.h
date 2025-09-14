#ifndef STOOL_H
#define STOOL_H

#include "score.h"

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

int
Scharcmp_bigger(char *a, char *b, int size_a, int size_b);

int
Scharcmp_smaller(char *a, char *b, int size_a, int size_b);

int
Scharcmp_equal(char *a, char *b, int size_a, int size_b);

char*
Sadd_1_char(char c1);

char*
Sadd_2_char(char c1, char c2);

char*
Sadd_3_char(char c1, char c2, char c3);

char*
Sadd_4_char(char c1, char c2, char c3, char c4);

int
Slen(char *str);

int
Sisdigit(char chr);

int
Sisstrdigit(char *str);

Sdll_func dll_get_func(char* func_name, char* dll_name);

char* Sstring_new(const char* fmt, ...);

char* remove_substr(char* str, const char* to_remove);

int if_file_exists(const char* filename);
int if_file_exists_in(const char* filename, const char* path);

int if_folder_exists(const char* foldername);
int if_folder_exists_in(const char* foldername, const char* path);

#endif