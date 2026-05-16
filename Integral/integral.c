#include "integral.h"
#include <math.h>

double integral(double (*f)(double), double a, double b, int n) {
  if (n <= 0)
    return 0.0;

  double h = (b - a) / n;
  double s = (f(a) + f(b)) / 2.0;

  for (int i = 1; i < n; i++) {
    s += f(a + i * h);
  }

  return s * h;
}

double f1(double x) { return x * x; }

double f2(double x) { return sin(x); }
