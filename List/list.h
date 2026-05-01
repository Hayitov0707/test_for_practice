#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int list_count(Node* head);

Node* list_insert_begin(Node* head, int value);
Node* list_insert_end(Node* head, int value);
Node* list_insert_at(Node* head, int value, int pos);

Node* list_delete_at(Node* head, int pos);

int list_find(Node* head, int pos, int* found);

void list_free(Node* head);

#endif

