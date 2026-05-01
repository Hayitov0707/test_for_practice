#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

int passed = 0;
int failed = 0;

void check_bool(const char *name, bool res, bool exp) {
    if (res == exp) {
        printf("✔ %s PASSED\n", name);
        passed++;
    } else {
        printf("❌ %s FAILED (%d != %d)\n", name, res, exp);
        failed++;
    }
}

void check_int(const char *name, int res, int exp) {
    if (res == exp) {
        printf("✔ %s PASSED\n", name);
        passed++;
    } else {
        printf("❌ %s FAILED (%d != %d)\n", name, res, exp);
        failed++;
    }
}

void test_init() {
    StackArray s;
    stack_init(&s);
    check_bool("empty after init", stack_empty(&s), true);
    check_bool("not full after init", stack_full(&s), false);
    check_int("size after init", stack_size(&s), 0);
}

void test_push_pop() {
    StackArray s;
    int val;
    stack_init(&s);

    check_bool("push 10", stack_push(&s, 10), true);
    check_bool("push 20", stack_push(&s, 20), true);
    check_bool("push 30", stack_push(&s, 30), true);

    check_int("size after pushes", stack_size(&s), 3);

    check_bool("peek ok", stack_peek(&s, &val), true);
    check_int("peek value", val, 30);

    check_bool("pop ok", stack_pop(&s, &val), true);
    check_int("pop value 1", val, 30);

    check_bool("pop ok 2", stack_pop(&s, &val), true);
    check_int("pop value 2", val, 20);

    check_bool("pop ok 3", stack_pop(&s, &val), true);
    check_int("pop value 3", val, 10);

    check_bool("empty after pops", stack_empty(&s), true);
    check_int("size after pops", stack_size(&s), 0);
}

void test_underflow() {
    StackArray s;
    int val;
    stack_init(&s);

    check_bool("pop from empty", stack_pop(&s, &val), false);
    check_bool("peek from empty", stack_peek(&s, &val), false);
}

void test_overflow() {
    StackArray s;
    stack_init(&s);

    for (int i = 0; i < STACK_MAX; i++) {
        check_bool("push in full test", stack_push(&s, i), true);
    }

    check_bool("stack full", stack_full(&s), true);
    check_int("size at full", stack_size(&s), STACK_MAX);
    check_bool("push overflow", stack_push(&s, 999), false);
}

int main() {
    printf("=== STACK TESTS ===\n\n");

    test_init();
    test_push_pop();
    test_underflow();
    test_overflow();

    printf("\nRESULT: passed=%d failed=%d\n", passed, failed);
    return failed;
}

