// array_list.h
#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "allocator.h"

typedef struct {
    IAllocator* alloc;
    void** data;
    size_t size;
    size_t capacity;
} ArrayList;

ArrayList array_list_create(IAllocator* alloc);
bool array_list_add(ArrayList* list, void* item);
void* array_list_get(ArrayList* list, size_t index);
void array_list_free(ArrayList* list);

#endif
