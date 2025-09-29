#include "smem.h"

void* Smem_RawMalloc(size_t size) {
    void* p = malloc(size);
    if (!p) {
        Serror_fatal_error("Smem_RawMalloc: cannot allocate %zu bytes\n", size);
        return NULL;
    }
    return p;
}

void* Smem_RawRealloc(void* ptr, size_t size) {
    void* p = realloc(ptr, size);
    if (!p && size != 0) {
        Serror_fatal_error("Smem_RawRealloc: cannot reallocate %zu bytes\n", size);
        return NULL;
    }
    return p;
}

void* Smem_RawCalloc(size_t nmemb, size_t size) {
    void* p = calloc(nmemb, size);
    if (!p) {
        Serror_fatal_error("Smem_RawCalloc: cannot allocate %zu elements of size %zu\n", nmemb, size);
        return NULL;
    }
    return p;
}

void Smem_RawFree(void* ptr) {
    free(ptr);
}

void* Smem_Malloc(size_t size) {
    if (size == 0) return NULL;
    void* p = Smem_RawMalloc(size);
    if (!p) return NULL;
    memset(p, 0, size);
    return p;
}

void* Smem_Realloc(void* ptr, size_t size) {
    if (size == 0) return NULL;
    void* p = Smem_RawRealloc(ptr, size);
    if (!p) return NULL;
    memset(p, 0, size);
    return p;
}

void* Smem_Calloc(size_t nmemb, size_t size) {
    if (nmemb == 0 || size == 0) return NULL;
    void* p = Smem_RawCalloc(nmemb, size);
    if (!p) return NULL;
    memset(p, 0, nmemb * size);
    return p;
}

void Smem_Free(void* ptr) {
    if (!ptr) return;
    Smem_RawFree(ptr);
}