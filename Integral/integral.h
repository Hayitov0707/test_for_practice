#ifndef INTEGRAL_H
#define INTEGRAL_H

// Чтобы M_PI был доступен во всех файлах
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double integral(double (*f)(double), double a, double b, int n);

// тестовые функции
double f1(double x);
double f2(double x);

#endif

