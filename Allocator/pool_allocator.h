// pool_allocator.h
#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include "allocator.h"

typedef struct PoolNode {
    struct PoolNode* next;
} PoolNode;

typedef struct {
    void* buffer;
    size_t block_size;
    PoolNode* free_list;
} PoolCtx;

IAllocator create_pool_alloc(PoolCtx* ctx, void* buffer, size_t total_size, size_t block_size);

#endif
#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include "allocator.h"

typedef struct PoolNode {
    struct PoolNode* next;
} PoolNode;

typedef struct {
    void* buffer;
    size_t block_size;
    PoolNode* free_list;
} PoolCtx;

IAllocator create_pool_alloc(PoolCtx* ctx, void* buffer, size_t total_size, size_t block_size);

#endif
