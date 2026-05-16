#include "list.h"
#include <assert.h>
#include <stdio.h>

int tests_passed = 0;
int tests_failed = 0;

void check_int(const char *name, int result, int expected) {
  if (result == expected) {
    printf("✔ %s PASSED (res=%d)\n", name, result);
    tests_passed++;
  } else {
    printf("❌ %s FAILED (res=%d expected=%d)\n", name, result, expected);
    tests_failed++;
  }
}

void test_count() {
  Node *list = NULL;
  list = list_insert_begin(list, 10);
  list = list_insert_begin(list, 20);

  check_int("count test", list_count(list), 2);

  list_free(list);
}

void test_insert_end() {
  Node *list = NULL;
  list = list_insert_end(list, 1);
  list = list_insert_end(list, 2);
  list = list_insert_end(list, 3);

  check_int("insert end count", list_count(list), 3);

  int found;
  int val = list_find(list, 2, &found);
  check_int("check middle value", val, 2);

  list_free(list);
}

void test_insert_at() {
  Node *list = NULL;
  list = list_insert_begin(list, 10);
  list = list_insert_begin(list, 20);

  list = list_insert_at(list, 99, 2);

  int found;
  int val = list_find(list, 2, &found);

  check_int("insert at pos", val, 99);

  list_free(list);
}

void test_delete() {
  Node *list = NULL;
  list = list_insert_end(list, 1);
  list = list_insert_end(list, 2);
  list = list_insert_end(list, 3);

  list = list_delete_at(list, 2);

  int found;
  int val = list_find(list, 2, &found);

  check_int("delete test", val, 3);

  list_free(list);
}

int main() {
  printf("=== TEST LIST ===\n\n");

  test_count();
  test_insert_end();
  test_insert_at();
  test_delete();

  printf("\nRESULT: passed=%d failed=%d\n", tests_passed, tests_failed);

  return tests_failed;
}
