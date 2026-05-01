#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define STACK_MAX 100

typedef struct {
    int data[STACK_MAX];
    int top;
} StackArray;

void stack_init(StackArray *s);
bool stack_empty(StackArray *s);
bool stack_full(StackArray *s);
bool stack_push(StackArray *s, int value);
bool stack_pop(StackArray *s, int *value);
bool stack_peek(StackArray *s, int *value);
int stack_size(StackArray *s);
void stack_print(StackArray *s);

#endif

