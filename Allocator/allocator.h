#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>
#include <stdbool.h>

// Макрос выравнивания памяти по границе 8 байт
#define ALIGN_SIZE(size) (((size) + 7) & ~7)

typedef struct IAllocator {
    void* (*alloc)(struct IAllocator* self, size_t size);
    void  (*free)(struct IAllocator* self, void* ptr);
    void* (*realloc)(struct IAllocator* self, void* ptr, size_t new_size);
    void  (*reset)(struct IAllocator* self);
    void* ctx;
} IAllocator;

// Заглушки для методов, которые не поддерживаются конкретным типом аллокатора
void stub_free(IAllocator* self, void* ptr);
void* stub_realloc(IAllocator* self, void* ptr, size_t size);
void stub_reset(IAllocator* self);

// Конструктор системного адаптера (основан на malloc/free)
IAllocator create_sys_alloc(void);

// Inline-хелперы для красивого синтаксиса вызова методов
static inline void* i_alloc(IAllocator* a, size_t sz) {
    return a->alloc(a, sz);
}

static inline void i_free(IAllocator* a, void* p) {
    a->free(a, p);
}

static inline void* i_realloc(IAllocator* a, void* p, size_t sz) {
    return a->realloc(a, p, sz);
}

static inline void i_reset(IAllocator* a) {
    a->reset(a);
}

#endif // ALLOCATOR_H
