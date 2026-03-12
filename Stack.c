#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_MAX 100

typedef struct {
    int data[STACK_MAX];
    int top;
} StackArray;

void stack_init(StackArray *s) {
    s->top = -1;
}

bool stack_empty(StackArray *s) {
    return s->top == -1;
}

bool stack_full(StackArray *s) {
    return s->top == STACK_MAX - 1;
}

bool stack_push(StackArray *s, int value) {
    if (stack_full(s)) {
        printf("Ошибка: стек переполнен\n");
        return false;
    }
    s->data[++(s->top)] = value;
    return true;
}

bool stack_pop(StackArray *s, int *value) {
    if (stack_empty(s)) {
        printf("Ошибка: стек пуст\n");
        return false;
    }
    *value = s->data[(s->top)--];
    return true;
}

bool stack_peek(StackArray *s, int *value) {
    if (stack_empty(s)) {
        printf("Ошибка: стек пуст\n");
        return false;
    }
    *value = s->data[s->top];
    return true;
}

int stack_size(StackArray *s) {
    return s->top + 1;
}

void stack_print(StackArray *s) {
    printf("Стек (сверху вниз): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

int main() {
    StackArray s;
    stack_init(&s);
    int val;

    printf("=== Стек на массиве ===\n");
    printf("Стек пуст? %s\n", stack_empty(&s) ? "да" : "нет");

    printf("Добавляем 10, 20, 30\n");
    stack_push(&s, 10);
    stack_push(&s, 20);
    stack_push(&s, 30);
    stack_print(&s);
    printf("Размер: %d\n", stack_size(&s));

    printf("Верхний элемент (peek): ");
    if (stack_peek(&s, &val)) printf("%d\n", val);

    printf("Удаляем элемент: ");
    if (stack_pop(&s, &val)) printf("%d\n", val);
    stack_print(&s);

    printf("Удаляем элемент: ");
    if (stack_pop(&s, &val)) printf("%d\n", val);
    stack_print(&s);

    printf("Удаляем элемент: ");
    if (stack_pop(&s, &val)) printf("%d\n", val);
    stack_print(&s);

    printf("Попытка удалить из пустого стека:\n");
    stack_pop(&s, &val);

    printf("Добавляем 50, 60\n");
    stack_push(&s, 50);
    stack_push(&s, 60);
    stack_print(&s);
    printf("Размер: %d\n", stack_size(&s));

    return 0;
}
