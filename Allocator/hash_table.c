// hash_table.c
#include "hash_table.h"
#include <string.h>

static size_t hash_func(const char* key, size_t num_buckets) {
    size_t hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % num_buckets;
}

HashTable hash_table_create(IAllocator* alloc, size_t num_buckets) {
    HashTable table = { .alloc = alloc, .buckets = NULL, .num_buckets = num_buckets };
    table.buckets = (HTItem**)i_alloc(alloc, num_buckets * sizeof(HTItem*));
    if (table.buckets) {
        memset(table.buckets, 0, num_buckets * sizeof(HTItem*));
    }
    return table;
}

bool hash_table_insert(HashTable* table, const char* key, void* value) {
    if (!table->buckets) return false;
    size_t idx = hash_func(key, table->num_buckets);
    HTItem* cur = table->buckets[idx];
    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            cur->value = value;
            return true;
        }
        cur = cur->next;
    }
    HTItem* item = (HTItem*)i_alloc(table->alloc, sizeof(HTItem));
    if (!item) return false;
    
    size_t key_len = strlen(key) + 1;
    item->key = (char*)i_alloc(table->alloc, key_len);
    if (!item->key) {
        i_free(table->alloc, item);
        return false;
    }
    memcpy(item->key, key, key_len);
    item->value = value;
    item->next = table->buckets[idx];
    table->buckets[idx] = item;
    return true;
}

void* hash_table_get(HashTable* table, const char* key) {
    if (!table->buckets) return NULL;
    size_t idx = hash_func(key, table->num_buckets);
    HTItem* cur = table->buckets[idx];
    while (cur) {
        if (strcmp(cur->key, key) == 0) return cur->value;
        cur = cur->next;
    }
    return NULL;
}

bool hash_table_remove(HashTable* table, const char* key) {
    if (!table->buckets) return false;
    size_t idx = hash_func(key, table->num_buckets);
    HTItem* cur = table->buckets[idx];
    HTItem* prev = NULL;
    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            if (prev) prev->next = cur->next;
            else table->buckets[idx] = cur->next;
            i_free(table->alloc, cur->key);
            i_free(table->alloc, cur);
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

void hash_table_free(HashTable* table) {
    if (!table->buckets) return;
    for (size_t i = 0; i < table->num_buckets; i++) {
        HTItem* cur = table->buckets[i];
        while (cur) {
            HTItem* tmp = cur;
            cur = cur->next;
            i_free(table->alloc, tmp->key);
            i_free(table->alloc, tmp);
        }
    }
    i_free(table->alloc, table->buckets);
    table->buckets = NULL;
}
