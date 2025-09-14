#ifndef SMETA_H
#define SMETA_H

#include "sobj.h"

struct Smeta {
    struct Sobj* (*mm_add)(struct Sobj*, struct Sobj*); // +
    struct Sobj* (*mm_sub)(struct Sobj*, struct Sobj*); // -
    struct Sobj* (*mm_mul)(struct Sobj*, struct Sobj*); // *
    struct Sobj* (*mm_div)(struct Sobj*, struct Sobj*); // /

    struct Sobj* (*mm_eq)(struct Sobj*, struct Sobj*); // ==
    struct Sobj* (*mm_ne)(struct Sobj*, struct Sobj*); // !=
    struct Sobj* (*mm_gt)(struct Sobj*, struct Sobj*); // >
    struct Sobj* (*mm_ge)(struct Sobj*, struct Sobj*); // >=
    struct Sobj* (*mm_lt)(struct Sobj*, struct Sobj*); // <
    struct Sobj* (*mm_le)(struct Sobj*, struct Sobj*); // <=

    struct Sobj* (*mm_call)(struct Sobj*, struct Sobj*); // ()
    struct Sobj* (*mm_index)(struct Sobj*, struct Sobj*); // []

    struct Sobj* (*mm_tostring)(struct Sobj*); // to string
    struct Sobj* (*mm_type)(struct Sobj*); // type

};
struct Smeta* Smeta_new(void);

void Smeta_set(struct Sobj* obj, const char* name, void* fn);

#endif // SMETA_H