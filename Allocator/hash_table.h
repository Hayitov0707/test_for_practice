// hash_table.h
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "allocator.h"

typedef struct HTItem {
    char* key;
    void* value;
    struct HTItem* next;
} HTItem;

typedef struct {
    IAllocator* alloc;
    HTItem** buckets;
    size_t num_buckets;
} HashTable;

HashTable hash_table_create(IAllocator* alloc, size_t num_buckets);
bool hash_table_insert(HashTable* table, const char* key, void* value);
void* hash_table_get(HashTable* table, const char* key);
bool hash_table_remove(HashTable* table, const char* key);
void hash_table_free(HashTable* table);

#endif
