#include "quadratic.h"
#include <math.h>
#include <stdio.h>

int passed = 0;
int failed = 0;

void check_int(const char *name, int res, int exp) {
  if (res == exp) {
    printf("✔ %s PASSED\n", name);
    passed++;
  } else {
    printf("❌ %s FAILED (%d != %d)\n", name, res, exp);
    failed++;
  }
}

void check_double(const char *name, double res, double exp) {
  if (fabs(res - exp) < EPS) {
    printf("✔ %s PASSED\n", name);
    passed++;
  } else {
    printf("❌ %s FAILED (%g != %g)\n", name, res, exp);
    failed++;
  }
}

void test1() {
  double r[2];
  check_int("a=0", quadratic(0, 1, 1, r), -1);
}

void test2() {
  double r[2];
  int n = quadratic(1, 0, -1, r);
  check_int("two roots", n, 2);
  check_double("x1", r[0], -1);
  check_double("x2", r[1], 1);
}

void test3() {
  double r[2];
  int n = quadratic(1, 0, 0, r);
  check_int("one root", n, 1);
  check_double("root", r[0], 0);
}

void test4() {
  double r[2];
  check_int("no roots", quadratic(1, 0, 1, r), 0);
}

void test5() {
  double r[2];
  int n = quadratic(1, 0, -1e-13, r);
  check_int("eps root", n, 1);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();

  printf("\npassed=%d failed=%d\n", passed, failed);
  return failed;
}
