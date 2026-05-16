#include "quadratic.h"
#include <math.h>

int quadratic(double a, double b, double c, double roots[2]) {
  if (fabs(a) < EPS)
    return -1;

  double D = b * b - 4.0 * a * c;

  if (fabs(D) < EPS)
    D = 0.0;

  if (D < 0.0)
    return 0;

  if (D == 0.0) {
    roots[0] = -b / (2.0 * a);
    return 1;
  }

  double sqrtD = sqrt(D);

  double x1 = (-b - sqrtD) / (2.0 * a);
  double x2 = (-b + sqrtD) / (2.0 * a);

  if (x1 > x2) {
    double t = x1;
    x1 = x2;
    x2 = t;
  }

  roots[0] = x1;
  roots[1] = x2;

  return 2;
}
