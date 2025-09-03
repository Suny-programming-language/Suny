#ifndef SCLASS_H
#define SCLASS_H

#include "stype.h"
#include "suny.h"

struct Sclass*
Sclass_new
(void);

int 
Sclass_free
(struct Sclass* sclass);

struct Sclass* 
Sclass_store_member
(struct Sclass* sclass, struct Sobj* member);

#endif // SCLASS_H