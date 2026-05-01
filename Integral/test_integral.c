#include <assert.h>
#include <math.h>

#include "integral.h"

// Test 1: ∫ x^2 dx от 0 до 1 = 1/3
void test_integral_x2() {
    // Arrange
    double a = 0.0;
    double b = 1.0;
    int n = 1000;
    double eps = 1e-5;

    // Act
    double res = integral(f1, a, b, n);

    // Assert
    assert(fabs(res - 0.333333) < eps);
}

// Test 2: ∫ sin(x) dx от 0 до pi = 2
void test_integral_sin() {
    // Arrange
    double a = 0.0;
    double b = M_PI;
    int n = 1000;
    double eps = 1e-5;

    // Act
    double res = integral(f2, a, b, n);

    // Assert
    assert(fabs(res - 2.0) < eps);
}

// Test 3: некорректное n
void test_integral_invalid_n() {
    // Arrange
    double a = 0.0;
    double b = 1.0;

    // Act
    double res = integral(f1, a, b, 0);

    // Assert
    assert(res == 0.0);
}

int main() {
    test_integral_x2();
    test_integral_sin();
    test_integral_invalid_n();
    return 0;
}

