#ifndef SCLASS_H
#define SCLASS_H

#include "stype.h"
#include "score.h"
#include "scopy.h"
#include "sframe.h"

struct Sclass*
Sclass_new
(void);

int 
Sclass_free
(struct Sclass* sclass);

struct Sclass* 
Sclass_store_object
(struct Sclass* sclass, struct Sframe* frame, int address);

struct Sclass* 
Sclass_store_local_obj
(struct Sclass* sclass, struct Sframe* frame, struct Sobj* value, int address);

struct Sobj* 
Sclass_get_object
(struct Sclass* sclass, int address);

struct Sobj* 
Sclass_push_obj
(struct Sclass* sclass, struct Sobj* obj);

struct Sobj*
Sobj_make_class(struct Sclass* sclass);

struct Sobj*
Sobj_creat_a_copy_version_of_class(struct Sclass* sclass);

#endif // SCLASS_H