// array_list.c
#include "array_list.h"
#include <string.h>

ArrayList array_list_create(IAllocator* alloc) {
    ArrayList list = { .alloc = alloc, .data = NULL, .size = 0, .capacity = 0 };
    return list;
}

bool array_list_add(ArrayList* list, void* item) {
    if (list->size >= list->capacity) {
        size_t new_cap = list->capacity == 0 ? 4 : list->capacity * 2;
        void* new_data = i_realloc(list->alloc, list->data, new_cap * sizeof(void*));
        
        if (!new_data) {
            new_data = i_alloc(list->alloc, new_cap * sizeof(void*));
            if (!new_data) return false;
            if (list->data) {
                memcpy(new_data, list->data, list->size * sizeof(void*));
                i_free(list->alloc, list->data);
            }
        }
        list->data = (void**)new_data;
        list->capacity = new_cap;
    }
    list->data[list->size++] = item;
    return true;
}

void* array_list_get(ArrayList* list, size_t index) {
    if (index >= list->size) return NULL;
    return list->data[index];
}

void array_list_free(ArrayList* list) {
    if (list->data) {
        i_free(list->alloc, list->data);
        list->data = NULL;
    }
    list->size = 0;
    list->capacity = 0;
}
