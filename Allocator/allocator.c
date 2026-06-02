#include "allocator.h"
#include <stdlib.h>

void stub_free(IAllocator* self, void* ptr) {
    (void)self; 
    (void)ptr;
}

void* stub_realloc(IAllocator* self, void* ptr, size_t size) {
    (void)self; 
    (void)ptr; 
    (void)size;
    return NULL;
}

void stub_reset(IAllocator* self) {
    (void)self;
}

static void* sys_alloc_impl(IAllocator* self, size_t size) {
    (void)self;
    return malloc(size);
}

static void sys_free_impl(IAllocator* self, void* ptr) {
    (void)self;
    free(ptr);
}

static void* sys_realloc_impl(IAllocator* self, void* ptr, size_t new_size) {
    (void)self;
    return realloc(ptr, new_size);
}

IAllocator create_sys_alloc(void) {
    IAllocator a = {
        .alloc = sys_alloc_impl,
        .free = sys_free_impl,
        .realloc = sys_realloc_impl,
        .reset = stub_reset,
        .ctx = NULL
    };
    return a;
}
