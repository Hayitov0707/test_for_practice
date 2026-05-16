#include "stack.h"
#include <stdio.h>

void stack_init(StackArray *s) { s->top = -1; }

bool stack_empty(StackArray *s) { return s->top == -1; }

bool stack_full(StackArray *s) { return s->top == STACK_MAX - 1; }

bool stack_push(StackArray *s, int value) {
  if (stack_full(s)) {
    return false;
  }
  s->data[++(s->top)] = value;
  return true;
}

bool stack_pop(StackArray *s, int *value) {
  if (stack_empty(s)) {
    return false;
  }
  *value = s->data[(s->top)--];
  return true;
}

bool stack_peek(StackArray *s, int *value) {
  if (stack_empty(s)) {
    return false;
  }
  *value = s->data[s->top];
  return true;
}

int stack_size(StackArray *s) { return s->top + 1; }

void stack_print(StackArray *s) {
  printf("Стек (сверху вниз): ");
  for (int i = s->top; i >= 0; i--) {
    printf("%d ", s->data[i]);
  }
  printf("\n");
}
