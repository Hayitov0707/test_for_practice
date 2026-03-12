#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int list_count(Node* head) {
    int cnt = 0;
    while (head != NULL) {
        cnt++;
        head = head->next;
    }
    return cnt;
}

Node* list_insert_begin(Node* head, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = head;
    return new_node;
}

Node* list_insert_end(Node* head, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    if (head == NULL) return new_node;
    Node* cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = new_node;
    return head;
}

Node* list_insert_at(Node* head, int value, int pos) {
    if (pos < 1) {
        printf("Ошибка: позиция < 1\n");
        return head;
    }
    if (pos == 1) return list_insert_begin(head, value);
    Node* cur = head;
    for (int i = 1; i < pos - 1 && cur != NULL; i++) cur = cur->next;
    if (cur == NULL) {
        printf("Ошибка: позиция %d слишком велика\n", pos);
        return head;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = cur->next;
    cur->next = new_node;
    return head;
}

Node* list_delete_at(Node* head, int pos) {
    if (head == NULL) {
        printf("Ошибка: список пуст\n");
        return NULL;
    }
    if (pos < 1) {
        printf("Ошибка: позиция < 1\n");
        return head;
    }
    if (pos == 1) {
        Node* temp = head->next;
        free(head);
        return temp;
    }
    Node* cur = head;
    for (int i = 1; i < pos - 1 && cur->next != NULL; i++) cur = cur->next;
    if (cur->next == NULL) {
        printf("Ошибка: позиция %d слишком велика\n", pos);
        return head;
    }
    Node* temp = cur->next;
    cur->next = temp->next;
    free(temp);
    return head;
}

int list_find(Node* head, int pos, int* found) {
    *found = 0;
    if (pos < 1 || head == NULL) return 0;
    Node* cur = head;
    for (int i = 1; i < pos && cur != NULL; i++) cur = cur->next;
    if (cur != NULL) {
        *found = 1;
        return cur->data;
    }
    return 0;
}

void list_print(Node* head) {
    printf("Список: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void list_free(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* list = NULL;
    int found, val;

    printf("=== Односвязный список ===\n");
    printf("Начальное количество: %d\n", list_count(list));

    list = list_insert_begin(list, 10);
    list = list_insert_begin(list, 20);
    list = list_insert_begin(list, 30);
    printf("После добавления в начало (30,20,10):\n");
    list_print(list);

    list = list_insert_end(list, 40);
    list = list_insert_end(list, 50);
    printf("После добавления в конец (40,50):\n");
    list_print(list);

    list = list_insert_at(list, 99, 3);
    printf("Вставка 99 на позицию 3:\n");
    list_print(list);

    list = list_insert_at(list, 77, 1);
    printf("Вставка 77 на позицию 1:\n");
    list_print(list);

    list = list_insert_at(list, 88, 8);
    printf("Вставка 88 на позицию 8:\n");
    list_print(list);

    val = list_find(list, 4, &found);
    if (found) printf("Элемент на позиции 4: %d\n", val);
    else printf("Позиция 4 не найдена\n");

    list = list_delete_at(list, 1);
    printf("Удаление позиции 1:\n");
    list_print(list);

    list = list_delete_at(list, 5);
    printf("Удаление позиции 5:\n");
    list_print(list);

    list = list_delete_at(list, 10); // ошибка
    printf("Попытка удалить позицию 10:\n");
    list_print(list);

    list_free(list);
    printf("Память освобождена\n");

    return 0;
}
