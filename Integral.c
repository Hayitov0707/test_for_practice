#include <stdio.h>
#include <math.h>

// Fix: Manually define M_PI if it is not provided by the compiler (common in -std=c11)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function to calculate the definite integral using the trapezoidal rule
double integral(double (*f)(double), double a, double b, int n) {
    if (n <= 0) return 0.0;
    double h = (b - a) / n;
    double s = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < n; i++) {
        s += f(a + i * h);
    }
    return s * h;
}

// Example integrand functions
double f1(double x) {
    return x * x;
}

double f2(double x) {
    return sin(x);
}

int main() {
    double a, b;
    int n = 1000;

    // Integral of x^2 from 0 to 1
    a = 0.0; b = 1.0;
    double res1 = integral(f1, a, b, n);
    printf("Integral of x^2 from %.2f to %.2f = %.6f (expected ~0.333333)\n", a, b, res1);

    // Integral of sin(x) from 0 to pi
    a = 0.0; b = M_PI;
    double res2 = integral(f2, a, b, n);
    printf("Integral of sin(x) from %.2f to %.2f = %.6f (expected 2.0)\n", a, b, res2);

    return 0;
}
