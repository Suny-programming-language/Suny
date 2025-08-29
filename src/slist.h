#ifndef SLIST_H
#define SLIST_H

#include "suny.h"
#include "sobj.h"
#include "stype.h"

struct Sobj;

struct Slist* Slist_new(void);

struct Slist* Slist_add(struct Slist* list, struct Sobj* obj);

struct Sobj* Slist_get(struct Slist* list, int index);

struct Sobj* Sobj_make_list(struct Slist* list);

struct Slist* Slist_change_item(struct Slist* list, int index, struct Sobj* obj);

struct Slist* Slist_pop(struct Slist* list);

#endif