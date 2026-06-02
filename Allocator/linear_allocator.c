// linear_allocator.c
#include "linear_allocator.h"

static void* linear_alloc_impl(IAllocator* self, size_t size) {
    LinearCtx* ctx = (LinearCtx*)self->ctx;
    size_t aligned = ALIGN_SIZE(size);
    
    if (ctx->offset + aligned > ctx->size) {
        return NULL; // Превышен размер арены
    }
    
    void* ptr = (char*)ctx->buffer + ctx->offset;
    ctx->offset += aligned;
    return ptr;
}

static void linear_reset_impl(IAllocator* self) {
    LinearCtx* ctx = (LinearCtx*)self->ctx;
    ctx->offset = 0;
}

IAllocator create_linear_alloc(LinearCtx* ctx, void* buffer, size_t size) {
    ctx->buffer = buffer;
    ctx->size = size;
    ctx->offset = 0;
    
    IAllocator a = {
        .alloc = linear_alloc_impl,
        .free = stub_free,
        .realloc = stub_realloc,
        .reset = linear_reset_impl,
        .ctx = ctx
    };
    return a;
}
