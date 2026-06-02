// linear_allocator.h
#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include "allocator.h"

typedef struct {
    void* buffer;
    size_t size;
    size_t offset;
} LinearCtx;

IAllocator create_linear_alloc(LinearCtx* ctx, void* buffer, size_t size);

#endif
