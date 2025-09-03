#ifndef SEVAL_H
#define SEVAL_H

#include "sobj.h"
#include "sframe.h"
#include "sstr.h"
#include "sbool.h"
#include "slist.h"

int Slist_cmp(struct Slist *list1, struct Slist *list2);

struct Sobj *
Seval_add
(struct Sobj *obj1, struct Sobj *obj2);

struct Sobj *
Seval_sub
(struct Sobj *obj1, struct Sobj *obj2);

struct Sobj *
Seval_mul
(struct Sobj *obj1, struct Sobj *obj2);

struct Sobj *
Seval_div
(struct Sobj *obj1, struct Sobj *obj2);

struct Sobj *
Seval_bigger
(struct Sobj *obj1, struct Sobj *obj2);

struct Sobj *
Seval_smaller
(struct Sobj *obj1, struct Sobj *obj2);

struct Sobj *
Seval_equal
(struct Sobj *obj1, struct Sobj *obj2);

struct Sobj *
Seval_not_equal
(struct Sobj *obj1, struct Sobj *obj2);

struct Sobj *
Seval_bigger_and_equal
(struct Sobj *obj1, struct Sobj *obj2);

struct Sobj *
Seval_smaller_and_equal
(struct Sobj *obj1, struct Sobj *obj2);

#endif
