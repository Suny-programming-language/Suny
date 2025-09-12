#ifndef STABLE_H
#define STABLE_H

#include "sobj.h"

#define hash(x) 0

struct Sentry {
    char* key;

    int address;
    int hash;

    struct Sobj* value;
    struct Sentry* next;
};

struct Sstable {
    struct Sentry** buckets;

    int size;
    int capacity;
};

struct Sstable* Sstable_new();
void Sstable_free(struct Sstable* sstable);

struct Sentry* Sentry_new(char* key, int address, struct Sobj* value);
void Sentry_free(struct Sentry* sentry);

struct Sobj* Sstable_get(struct Sstable* sstable, char* key);
void Sstable_put(struct Sstable* sstable, char* key, struct Sobj* value);

struct Sobj* Sstable_remove(struct Sstable* sstable, char* key);

#endif // STABLE_H