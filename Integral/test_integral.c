#include <assert.h>
#include <math.h>

#include "integral.h"


void test_integral_x2() {
    // Arrange
    double a = 0.0;
    double b = 1.0;
    int n = 1000;
    double eps = 1e-5;

    double res = integral(f1, a, b, n);


    assert(fabs(res - 0.333333) < eps);
}


void test_integral_sin() {
    
    double a = 0.0;
    double b = M_PI;
    int n = 1000;
    double eps = 1e-5;

   
    double res = integral(f2, a, b, n);

    
    assert(fabs(res - 2.0) < eps);
}


void test_integral_invalid_n() {
    
    double a = 0.0;
    double b = 1.0;

    
    double res = integral(f1, a, b, 0);

    
    assert(res == 0.0);
}

int main() {
    test_integral_x2();
    test_integral_sin();
    test_integral_invalid_n();
    return 0;
}

