// queue.c
#include "queue.h"

Queue queue_create(IAllocator* alloc) {
    Queue q = { .alloc = alloc, .head = NULL, .tail = NULL };
    return q;
}

bool queue_push(Queue* q, void* val) {
    QNode* n = (QNode*)i_alloc(q->alloc, sizeof(QNode));
    if (!n) return false;
    n->data = val;
    n->next = NULL;
    if (!q->tail) {
        q->head = n;
        q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }
    return true;
}

void* queue_pop(Queue* q) {
    if (!q->head) return NULL;
    QNode* tmp = q->head;
    void* data = tmp->data;
    q->head = q->head->next;
    if (!q->head) {
        q->tail = NULL;
    }
    i_free(q->alloc, tmp);
    return data;
}

void queue_free(Queue* q) {
    while (q->head) {
        queue_pop(q);
    }
}
