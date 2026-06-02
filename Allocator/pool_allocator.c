// pool_allocator.c
#include "pool_allocator.h"

static void* pool_alloc_impl(IAllocator* self, size_t size) {
    PoolCtx* ctx = (PoolCtx*)self->ctx;
    if (size > ctx->block_size || !ctx->free_list) {
        return NULL; 
    }
    PoolNode* node = ctx->free_list;
    ctx->free_list = node->next;
    return (void*)node;
}

static void pool_free_impl(IAllocator* self, void* ptr) {
    if (!ptr) return;
    PoolCtx* ctx = (PoolCtx*)self->ctx;
    PoolNode* node = (PoolNode*)ptr;
    node->next = ctx->free_list;
    ctx->free_list = node;
}

IAllocator create_pool_alloc(PoolCtx* ctx, void* buffer, size_t total_size, size_t block_size) {
    size_t actual_block = ALIGN_SIZE(block_size);
    if (actual_block < sizeof(PoolNode)) {
        actual_block = ALIGN_SIZE(sizeof(PoolNode));
    }
    
    ctx->buffer = buffer;
    ctx->block_size = actual_block;
    ctx->free_list = NULL;
    
    size_t num_blocks = total_size / actual_block;
    char* ptr = (char*)buffer;
    
    for (size_t i = 0; i < num_blocks; i++) {
        PoolNode* node = (PoolNode*)(ptr + i * actual_block);
        node->next = ctx->free_list;
        ctx->free_list = node;
    }
    
    IAllocator a = {
        .alloc = pool_alloc_impl,
        .free = pool_free_impl,
        .realloc = stub_realloc,
        .reset = stub_reset,
        .ctx = ctx
    };
    return a;
}
