#ifndef SLABEL_H
#define SLABEL_H

#include "scode.h"
#include "score.h"
#include "max.h"
#include "sobj.h"

struct Spos {
    int address;
    int indexof;
};

struct Slabel_map {
    struct Scode *code;

    struct Spos label[MAX_LABEL_SIZE];

    int label_count;
    int label_size;

    int program_count;
    int program_size;
};

struct Spos 
Spos_new();

struct Slabel_map *
Slabel_map_new();

struct Spos 
Spos_set
(int address, int indexof);

int Slabel_map_free
(struct Slabel_map *label_map);

struct Slabel_map *
Slabel_map_set
(struct Slabel_map *label_map, struct Spos pos);

struct Spos 
Slabel_map_get
(struct Slabel_map *label_map, int address);

struct Slabel_map *
Slabel_map_set_program
(struct Scode *code);

#endif // SLABEL_H