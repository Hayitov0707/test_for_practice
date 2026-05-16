#include "list.h"

int list_count(Node *head) {
  int cnt = 0;
  while (head) {
    cnt++;
    head = head->next;
  }
  return cnt;
}

Node *list_insert_begin(Node *head, int value) {
  Node *n = (Node *)malloc(sizeof(Node));
  n->data = value;
  n->next = head;
  return n;
}

Node *list_insert_end(Node *head, int value) {
  Node *n = (Node *)malloc(sizeof(Node));
  n->data = value;
  n->next = NULL;

  if (!head)
    return n;

  Node *cur = head;
  while (cur->next)
    cur = cur->next;
  cur->next = n;

  return head;
}

Node *list_insert_at(Node *head, int value, int pos) {
  if (pos <= 1 || !head) {
    return list_insert_begin(head, value);
  }

  Node *cur = head;
  for (int i = 1; i < pos - 1 && cur->next; i++) {
    cur = cur->next;
  }

  Node *n = (Node *)malloc(sizeof(Node));
  n->data = value;
  n->next = cur->next;
  cur->next = n;

  return head;
}

Node *list_delete_at(Node *head, int pos) {
  if (!head || pos < 1)
    return head;

  if (pos == 1) {
    Node *tmp = head->next;
    free(head);
    return tmp;
  }

  Node *cur = head;
  for (int i = 1; i < pos - 1 && cur->next; i++) {
    cur = cur->next;
  }

  if (!cur->next)
    return head;

  Node *tmp = cur->next;
  cur->next = tmp->next;
  free(tmp);

  return head;
}

int list_find(Node *head, int pos, int *found) {
  *found = 0;
  if (!head || pos < 1)
    return 0;

  Node *cur = head;
  for (int i = 1; i < pos && cur; i++) {
    cur = cur->next;
  }

  if (!cur)
    return 0;

  *found = 1;
  return cur->data;
}

void list_free(Node *head) {
  while (head) {
    Node *tmp = head;
    head = head->next;
    free(tmp);
  }
}
