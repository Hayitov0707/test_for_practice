// buddy_allocator.c
#include "buddy_allocator.h"
#include <string.h>

static size_t get_order(size_t size) {
    size_t order = 0;
    size_t current = 1;
    while (current < size) {
        current <<= 1;
        order++;
    }
    return order;
}

static void* buddy_alloc_impl(IAllocator* self, size_t size) {
    BuddyCtx* ctx = (BuddyCtx*)self->ctx;
    size_t needed = size + sizeof(BuddyHeader);
    size_t order = get_order(needed);
    size_t min_order = get_order(ctx->min_block_size);
    if (order < min_order) order = min_order;
    
    size_t current_size = (size_t)1 << order;
    if (current_size > ctx->total_size) return NULL;
    
    char* ptr = (char*)ctx->buffer;
    char* end = ptr + ctx->total_size;
    
    while (ptr < end) {
        BuddyHeader* header = (BuddyHeader*)ptr;
        size_t block_size = (size_t)1 << header->order;
        
        if (header->is_free && header->order == order) {
            header->is_free = 0;
            return (void*)(ptr + sizeof(BuddyHeader));
        }
        
        if (header->is_free && header->order > order) {
            header->order--;
            size_t new_size = (size_t)1 << header->order;
            BuddyHeader* buddy = (BuddyHeader*)(ptr + new_size);
            buddy->order = header->order;
            buddy->is_free = 1;
            continue; 
        }
        ptr += block_size;
    }
    return NULL;
}

static void buddy_free_impl(IAllocator* self, void* ptr) {
    if (!ptr) return;
    BuddyCtx* ctx = (BuddyCtx*)self->ctx;
    char* block_ptr = (char*)ptr - sizeof(BuddyHeader);
    BuddyHeader* header = (BuddyHeader*)block_ptr;
    header->is_free = 1;
    
    while (1) {
        size_t block_size = (size_t)1 << header->order;
        if (block_size >= ctx->total_size) break;
        
        size_t relative_addr = (char*)header - (char*)ctx->buffer;
        size_t buddy_relative = relative_addr ^ block_size;
        char* buddy_ptr = (char*)ctx->buffer + buddy_relative;
        
        if (buddy_ptr < (char*)ctx->buffer || buddy_ptr >= (char*)ctx->buffer + ctx->total_size) {
            break;
        }
        
        BuddyHeader* buddy = (BuddyHeader*)buddy_ptr;
        if (buddy->is_free && buddy->order == header->order) {
            char* left_ptr = (char*)header < buddy_ptr ? (char*)header : buddy_ptr;
            BuddyHeader* left = (BuddyHeader*)left_ptr;
            left->order++;
            header = left;
        } else {
            break;
        }
    }
}

static void* buddy_realloc_impl(IAllocator* self, void* ptr, size_t new_size) {
    if (!ptr) return self->alloc(self, new_size);
    if (new_size == 0) {
        self->free(self, ptr);
        return NULL;
    }
    BuddyHeader* header = (BuddyHeader*)((char*)ptr - sizeof(BuddyHeader));
    size_t available_payload = ((size_t)1 << header->order) - sizeof(BuddyHeader);
    if (new_size <= available_payload) {
        return ptr;
    }
    void* new_ptr = self->alloc(self, new_size);
    if (!new_ptr) return NULL;
    memcpy(new_ptr, ptr, available_payload);
    self->free(self, ptr);
    return new_ptr;
}

IAllocator create_buddy_alloc(BuddyCtx* ctx, void* buffer, size_t total_size, size_t min_block_size) {
    ctx->buffer = buffer;
    ctx->total_size = total_size;
    ctx->min_block_size = min_block_size;
    
    BuddyHeader* root = (BuddyHeader*)buffer;
    root->order = get_order(total_size);
    root->is_free = 1;
    
    IAllocator a = {
        .alloc = buddy_alloc_impl,
        .free = buddy_free_impl,
        .realloc = buddy_realloc_impl,
        .reset = stub_reset,
        .ctx = ctx
    };
    return a;
}
