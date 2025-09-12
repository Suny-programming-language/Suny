#include "stable.h"

struct Sstable* Sstable_new() {
    struct Sstable* sstable = malloc(sizeof(struct Sstable));
    sstable->capacity = 1024;
    sstable->size = 0;

    sstable->buckets = malloc(sizeof(struct Sentry*) * sstable->capacity);

    return sstable;
}
void Sstable_free(struct Sstable* sstable) {
    free(sstable->buckets);
    free(sstable);
}

struct Sentry* Sentry_new(char* key, int address, struct Sobj* value) {
    struct Sentry* sentry = malloc(sizeof(struct Sentry));
    sentry->key = key;
    sentry->address = address;
    sentry->hash = hash(key);
    sentry->value = value;
    return sentry;
}

void Sentry_free(struct Sentry* sentry) {
    free(sentry);
}

struct Sobj* Sstable_get(struct Sstable* sstable, char* key) {
    for (int i = 0; i < sstable->size; i++) {
        struct Sentry* sentry = sstable->buckets[i];
        if (strcmp(sentry->key, key) == 0) {
            return sentry->value;
        }
    }

    return NULL;
}
void Sstable_put(struct Sstable* sstable, char* key, struct Sobj* value) {
    if (sstable->size >= sstable->capacity) {
        sstable->capacity *= 2;
        sstable->buckets = realloc(sstable->buckets, sizeof(struct Sentry*) * sstable->capacity);
    }

    struct Sentry* sentry = Sentry_new(key, sstable->size, value);
    sstable->buckets[sstable->size++] = sentry;
}

struct Sobj* Sstable_remove(struct Sstable* sstable, char* key) {
    for (int i = 0; i < sstable->size; i++) {
        struct Sentry* sentry = sstable->buckets[i];
        if (strcmp(sentry->key, key) == 0) {
            struct Sobj* value = sentry->value;
            sstable->buckets[i] = sstable->buckets[sstable->size - 1];
            sstable->buckets[sstable->size - 1] = NULL;
            sstable->size--;
            return value;
        }
    }

    return NULL;
}