// buddy_allocator.h
#ifndef BUDDY_ALLOCATOR_H
#define BUDDY_ALLOCATOR_H

#include "allocator.h"

typedef struct {
    size_t order;
    int is_free;
} BuddyHeader;

typedef struct {
    void* buffer;
    size_t total_size;
    size_t min_block_size;
} BuddyCtx;

IAllocator create_buddy_alloc(BuddyCtx* ctx, void* buffer, size_t total_size, size_t min_block_size);

#endif
