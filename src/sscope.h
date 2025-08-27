#ifndef SSCOPE_H
#define SSCOPE_H

#include "scompile.h"

struct Scope
new_scope(void);

int
add_scope(struct Scompiler *compiler, char *name, int address);

int
find_scope(struct Scompiler *compiler, char *name);

int
remove_scope(struct Scompiler *compiler, char *name);

#endif 