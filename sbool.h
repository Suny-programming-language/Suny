#ifndef SBOOL_H
#define SBOOL_H

#include "sobj.h"
#include "stype.h"

struct Sobj* Sobj_make_true();
struct Sobj* Sobj_make_false();

struct Sobj* Sobj_make_bool(int value);

#endif // SBOOL_H