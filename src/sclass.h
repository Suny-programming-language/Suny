#ifndef SCLASS_H
#define SCLASS_H

#include "stype.h"
#include "score.h"
#include "sframe.h"

struct Sclass*
Sclass_new
(void);

int 
Sclass_free
(struct Sclass* sclass);

struct Sclass* 
Sclass_store_member
(struct Sclass* sclass, struct Sframe* frame, int address);

struct Sclass* 
Sclass_store_object
(struct Sclass* sclass, struct Sobj* object);

struct Sobj* 
Sclass_get_object
(struct Sclass* sclass, int address);

#endif // SCLASS_H