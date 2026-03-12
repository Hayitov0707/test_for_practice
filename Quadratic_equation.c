#include <stdio.h>
#include <math.h>

#define EPS 1e-12

int quadratic(double a, double b, double c, double roots[2]) {
    if (a == 0.0) {
        return -1;
    }

    double D = b * b - 4.0 * a * c;

    if (D < 0.0) {
        if (D > -EPS) {
            D = 0.0;
        } else {
            return 0;
        }
    }

    if (D == 0.0) {
        roots[0] = -b / (2.0 * a);
        return 1;
    }

    double sqrtD = sqrt(D);
    double x1 = (-b - sqrtD) / (2.0 * a);
    double x2 = (-b + sqrtD) / (2.0 * a);

    if (x1 > x2) {
        double tmp = x1;
        x1 = x2;
        x2 = tmp;
    }

    roots[0] = x1;
    roots[1] = x2;
    return 2;
}

int main() {
    double roots[2];
    int n;

    printf("1) a=0:\n");
    n = quadratic(0.0, 1.0, 1.0, roots);
    if (n == -1) printf("   Ошибка: a = 0\n\n");

    printf("2) a=1, b=0, c=-1:\n");
    n = quadratic(1.0, 0.0, -1.0, roots);
    if (n == 2) printf("   Корни: %g, %g\n\n", roots[0], roots[1]);

    printf("3) a=1, b=0, c=0:\n");
    n = quadratic(1.0, 0.0, 0.0, roots);
    if (n == 1) printf("   Корень: %g\n\n", roots[0]);

    printf("4) a=1, b=0, c=1:\n");
    n = quadratic(1.0, 0.0, 1.0, roots);
    if (n == 0) printf("   Нет действительных корней\n\n");

    printf("5) a=1, b=0, c=-1e-7:\n");
    n = quadratic(1.0, 0.0, -1e-7, roots);
    if (n == 2) printf("   Корни: %g, %g\n\n", roots[0], roots[1]);

    printf("6) a=1, b=-1e10, c=-1:\n");
    n = quadratic(1.0, -1e10, -1.0, roots);
    if (n == 2) printf("   Корни: %g, %g\n\n", roots[0], roots[1]);

    printf("7) a=1, b=0, c=-1e-8:\n");
    n = quadratic(1.0, 0.0, -1e-8, roots);
    if (n == 2) printf("   Корни: %g, %g\n\n", roots[0], roots[1]);

    return 0;
}
