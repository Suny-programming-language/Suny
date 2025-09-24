#include "slabel.h"

struct Spos Spos_new() {
    struct Spos pos;
    pos.address = 0;
    pos.indexof = 0;
    return pos;
}

struct Slabel_map *Slabel_map_new() {
    struct Slabel_map *label_map = malloc(sizeof(struct Slabel_map));
    label_map->code = NULL;
    
    label_map->label_count = 0;
    label_map->label_size = 0;

    label_map->program_count = 0;
    label_map->program_size = 0;
    
    label_map->label[0] = Spos_new();
    return label_map;
}

int Slabel_map_free(struct Slabel_map *label_map) {
    free(label_map);
    return 0;
}

struct Spos Spos_set(int address, int indexof) {
    struct Spos pos;
    pos.address = address;
    pos.indexof = indexof;
    return pos;
}

struct Slabel_map *Slabel_map_set(struct Slabel_map *label_map, struct Spos pos) {
    label_map->label[label_map->label_count++] = pos;
    return label_map;
}

struct Spos Slabel_map_get(struct Slabel_map *label_map, int address) {
    for (int i = 0; i < label_map->label_count; i++) {
        if (label_map->label[i].address == address) {
            return label_map->label[i];
        }
    }

    printf("Error: label not found\n");
    return Spos_new();
}

struct Slabel_map *Slabel_map_set_program(struct Scode *code) {
    struct Slabel_map *label_map = Slabel_map_new();
    label_map->code = code;

    label_map->program_size = code->size;

    for (int i = 0; i < code->size; i++) {
        byte_t op = code->code[i];
        if (op == ADD_LABEL) {
            int address = code->code[i + 1];
            int indexof = i + 1;

            struct Spos pos = Spos_set(address, indexof);
            label_map = Slabel_map_set(label_map, pos);

            i += 1;
        }
    }

    return label_map;
}