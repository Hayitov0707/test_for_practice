#include "allocator.h"
#include "linear_allocator.h"
#include "pool_allocator.h"
#include "buddy_allocator.h"
#include "array_list.h"
#include "queue.h"
#include "hash_table.h"
#include <stdio.h>

static char linear_buffer[4096];
static char pool_buffer[4096];
static char buddy_buffer[65536]; // 64 KB для Buddy (обязательно степень 2!)

int main(void) {
    printf("=== Запуск сквозного тестирования аллокаторов ===\n\n");

    // 1. Контрольная группа: Системный Аллокатор
    IAllocator sys_alloc = create_sys_alloc();
    ArrayList list_sys = array_list_create(&sys_alloc);
    array_list_add(&list_sys, (void*)100);
    array_list_add(&list_sys, (void*)200);
    printf("[System Alloc] ArrayList: %ld, %ld\n", (long)array_list_get(&list_sys, 0), (long)array_list_get(&list_sys, 1));
    array_list_free(&list_sys);

    // 2. Линейный Аллокатор (Арена) + ArrayList
    LinearCtx lin_ctx;
    IAllocator lin_alloc = create_linear_alloc(&lin_ctx, linear_buffer, sizeof(linear_buffer));
    ArrayList list_lin = array_list_create(&lin_alloc);
    for(long i = 1; i <= 3; i++) {
        array_list_add(&list_lin, (void*)i);
    }
    printf("[Linear Alloc] ArrayList size: %zu, Последний: %ld\n", list_lin.size, (long)array_list_get(&list_lin, 2));
    i_reset(&lin_alloc); // Полный сброс арены

    // 3. Пул-Аллокатор + Очередь FIFO
    PoolCtx pool_ctx;
    IAllocator pool_alloc = create_pool_alloc(&pool_ctx, pool_buffer, sizeof(pool_buffer), sizeof(QNode));
    Queue q = queue_create(&pool_alloc);
    queue_push(&q, (void*)42);
    queue_push(&q, (void*)84);
    printf("[Pool Alloc] Извлечено из Queue: %ld\n", (long)queue_pop(&q));
    printf("[Pool Alloc] Извлечено из Queue: %ld\n", (long)queue_pop(&q));
    queue_free(&q);

    // 4. Buddy Аллокатор + Хэш-Таблица
    BuddyCtx buddy_ctx;
    IAllocator buddy_alloc = create_buddy_alloc(&buddy_ctx, buddy_buffer, sizeof(buddy_buffer), 32);
    HashTable ht = hash_table_create(&buddy_alloc, 8);
    hash_table_insert(&ht, "UserToken", (void*)777);
    hash_table_insert(&ht, "SessionID", (void*)888);
    printf("[Buddy Alloc] HashTable 'UserToken': %ld\n", (long)hash_table_get(&ht, "UserToken"));
    printf("[Buddy Alloc] HashTable 'SessionID': %ld\n", (long)hash_table_get(&ht, "SessionID"));
    hash_table_remove(&ht, "UserToken");
    printf("[Buddy Alloc] После удаления 'UserToken': %p\n", hash_table_get(&ht, "UserToken"));
    hash_table_free(&ht);

    printf("\n=== Тестирование завершено без аварийных сбоев! ===\n");
    return 0;
}
