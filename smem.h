#ifndef SMEM_H
#define SMEM_H

#include "score.h"  
#include "serror.h"

void* Smem_RawMalloc(size_t size);

void* Smem_RawRealloc(void* ptr, size_t size);

void* Smem_RawCalloc(size_t nmemb, size_t size);

void Smem_RawFree(void* ptr);

void* Smem_Malloc(size_t size);

void* Smem_Realloc(void* ptr, size_t size);

void* Smem_Calloc(size_t nmemb, size_t size);

void Smem_Free(void* ptr);

#endif // SMEM_H