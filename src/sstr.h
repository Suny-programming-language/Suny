#ifndef SSTR_H
#define SSTR_H

#include "sobj.h"

struct Sstr *Sstr_new(void);

struct Sstr *Sstr_new_from_char(char *chr, int size);

void Sstr_free(struct Sstr *str);

struct Sstr *Sstr_add(struct Sstr *str1, struct Sstr *str2);

struct Sstr *Sstr_mul(struct Sstr *str, int n);

struct Sobj* Sobj_make_str_obj(struct Sstr *str);

struct Sobj *Sobj_make_str(char* str, int size);

#endif