// queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include "allocator.h"

typedef struct QNode {
    void* data;
    struct QNode* next;
} QNode;

typedef struct {
    IAllocator* alloc;
    QNode* head;
    QNode* tail;
} Queue;

Queue queue_create(IAllocator* alloc);
bool queue_push(Queue* q, void* val);
void* queue_pop(Queue* q);
void queue_free(Queue* q);

#endif
