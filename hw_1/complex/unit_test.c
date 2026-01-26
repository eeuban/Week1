#include "complex.h"
#include <math.h>
#include "gtest/gtest.h"

namespace{

    TEST(Complex, add){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {22.0, 4.0};
        const complex c = {-13.2, -15.4};
        const complex d = {INFINITY, 10.0};
        const complex e = {INFINITY-2.0, 10.0};
        const complex f = {1.0, 0.0};
        const complex g = {-INFINITY, 10.0};

        const complex actual = add(a, b);
        const complex actual1 = add(a, c);

        // Testing is_infinite functionality.
        const complex actual2 = add(a, d);
        const complex actual3 = add(e, f);
        const complex actual4 = add(g, c);

        EXPECT_DOUBLE_EQ(actual.real, 32.0);
        EXPECT_DOUBLE_EQ(actual.im, 9.0);
        EXPECT_DOUBLE_EQ(actual1.real, -3.2);
        EXPECT_DOUBLE_EQ(actual1.im, -10.4);
        EXPECT_DOUBLE_EQ(actual2.real, -1.0);
        EXPECT_DOUBLE_EQ(actual2.im, -1.0);
        // Should be equal to INFINITY-1 == INFINITY due to IEEE 754 standard. 
        EXPECT_DOUBLE_EQ(actual3.real, -1.0);
        EXPECT_DOUBLE_EQ(actual3.im, -1.0);
        EXPECT_DOUBLE_EQ(actual4.real, -1.0);
        EXPECT_DOUBLE_EQ(actual4.im, -1.0);
    };

    TEST(Complex, subtract){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {22.0, 4.0};
        const complex c = {-13.2, -15.4};

        const complex d = {INFINITY, -3.2};
        const complex e = {8.0, INFINITY};
        const complex f = {-INFINITY, -3.2};
        const complex g = {INFINITY-2.0, 3.2};

        const complex actual = subtract(a, b);
        const complex actual1 = subtract(a, c);

        const complex actual2 = subtract(c, d);
        const complex actual3 = subtract(e, b);

        const complex actual4 = subtract(f, a);
        const complex actual5 = subtract(g, a);

        EXPECT_DOUBLE_EQ(actual.real, -12.0);
        EXPECT_DOUBLE_EQ(actual.im, 1);
        EXPECT_DOUBLE_EQ(actual1.real, 23.2);
        EXPECT_DOUBLE_EQ(actual1.im, 20.4);
        EXPECT_DOUBLE_EQ(actual2.real, -1);
        EXPECT_DOUBLE_EQ(actual2.im, -1);
        EXPECT_DOUBLE_EQ(actual3.real, -1);
        EXPECT_DOUBLE_EQ(actual3.im, -1);
        EXPECT_DOUBLE_EQ(actual4.real, -1);
        EXPECT_DOUBLE_EQ(actual4.im, -1);
        EXPECT_DOUBLE_EQ(actual5.real, -1);
        EXPECT_DOUBLE_EQ(actual5.im, -1);
    };

    TEST(Complex, multiply){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {22.0, 4.0};
        const complex c = {-13.2, -15.4};
        const complex d = {0.0, -1.0};
        const complex e = {100000000000.0, 100000000000.0};
        const complex f = {INFINITY, 1000000000000000000000000000.0};

        const complex actual = multiply(a, b);
        const complex actual1 = multiply(a, c);
        const complex actual2 = multiply(c, d);
        const complex actual3 = multiply(e, b);
        const complex actual4 = multiply(e, f);

        EXPECT_DOUBLE_EQ(actual.real, 220.0);
        EXPECT_DOUBLE_EQ(actual.im, 20.0);
        EXPECT_DOUBLE_EQ(actual1.real, -132.0);
        EXPECT_DOUBLE_EQ(actual1.im, -77);
        EXPECT_DOUBLE_EQ(actual2.real, 0.0);
        EXPECT_DOUBLE_EQ(actual2.im, 15.4);
        EXPECT_DOUBLE_EQ(actual3.real, 2200000000000.0);
        EXPECT_DOUBLE_EQ(actual3.im, 400000000000.0);
        EXPECT_DOUBLE_EQ(actual4.real, -1);
        EXPECT_DOUBLE_EQ(actual4.im, -1);
    };

    TEST(Complex, divide){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {22.0, 4.0};
        const complex azero = {0., 5.0};
        const complex bzero = {.6, 0.};
        const complex d = {3.23, 58973};
        const complex e = {INFINITY, 3.09732894};
        const complex f = {0.0000000000004, 7.23098472};

        const complex actual = divide(a, b);
        const complex actual1 = divide(azero, b);
        const complex actual2 = divide(a, bzero);
        const complex actual3 = divide(b, d);
        const complex actual4 = divide(e, f);

        EXPECT_DOUBLE_EQ(actual.real, 10.0/22.0);
        EXPECT_DOUBLE_EQ(actual.im, 1.25);
        EXPECT_DOUBLE_EQ(actual1.real, 0);
        EXPECT_DOUBLE_EQ(actual1.im, 5/4.0);
        EXPECT_DOUBLE_EQ(actual2.real, INFINITY);
        EXPECT_DOUBLE_EQ(actual2.im, INFINITY);
        EXPECT_DOUBLE_EQ(actual3.real, 22.0/3.23);
        EXPECT_DOUBLE_EQ(actual3.im, 4.0/58973);
        EXPECT_DOUBLE_EQ(actual4.real, -1);
        EXPECT_DOUBLE_EQ(actual4.im, -1);
    };

    TEST(Complex, conjugate){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {10.0, 0.0};
        const complex c = {0.0, 0.0};
        
        const complex actual = conjugate(a);
        const complex actual1 = conjugate(b);
        const complex actual2 = conjugate(c);

        EXPECT_DOUBLE_EQ(actual.real, a.real);
        EXPECT_DOUBLE_EQ(actual.im, -5.0);
        EXPECT_DOUBLE_EQ(actual1.real, b.real);
        EXPECT_DOUBLE_EQ(actual1.im, 0.0);
        EXPECT_DOUBLE_EQ(actual1.real, b.real);
        EXPECT_DOUBLE_EQ(actual1.im, 0.0);
    };

    TEST(Complex, 2polar){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {13.7, -36093};
        
        const polar actual = to_polar(a);
        const polar actual1 = to_polar(b);
        EXPECT_DOUBLE_EQ(actual.r, 5*sqrt(5));
        EXPECT_DOUBLE_EQ(actual.theta, atan2(5.0, 10.0));
        EXPECT_DOUBLE_EQ(actual1.r, sqrt((18769.0/100.0) + pow(-36093.0,2)));
        EXPECT_DOUBLE_EQ(actual1.theta, atan2(-36093, 13.7));
    };

    TEST(Complex, power){
        // Vars
        const complex a = {10.0, 5.0};

        
        const complex actual = power(a, 2);
        const complex actual1 = power(a, 15);
        const complex actual2 = power(a, -1);
        const complex actual3 = power(a, -5);
        const complex actual4 = power(a, 100000);

        EXPECT_DOUBLE_EQ(actual.real, 100.0);
        EXPECT_DOUBLE_EQ(actual.im, 25.0);
        EXPECT_DOUBLE_EQ(actual1.real, 1000000000000000.0);
        EXPECT_DOUBLE_EQ(actual1.im, 30517578125.0);
        EXPECT_DOUBLE_EQ(actual2.real, 1.0/10.0);
        EXPECT_DOUBLE_EQ(actual2.im, 1.0/5.0);
        EXPECT_DOUBLE_EQ(actual3.real, 1.0/100000.0);
        EXPECT_DOUBLE_EQ(actual3.im, 1.0/3125.0);
        EXPECT_DOUBLE_EQ(actual4.real, -1.0);
        EXPECT_DOUBLE_EQ(actual4.im, -1.0);
    };

    TEST(Complex, magnitude){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {678345e300, 530485e300};
        
        double actual = magnitude(a);
        double actual1 = magnitude(b);
        EXPECT_DOUBLE_EQ(actual, 5*sqrt(5));
        EXPECT_DOUBLE_EQ(actual1, -1.0);
    };

    TEST(Complex, equals){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {10.0, 5.0};
        const complex c = {11.0, 5.0};
        const complex d = {10.0, 6.0};
        const complex e = {15.3, 13.2};
        
        EXPECT_DOUBLE_EQ(1, equals(a, b));
        EXPECT_DOUBLE_EQ(0, equals(a, c));
        EXPECT_DOUBLE_EQ(0, equals(a, d));
        EXPECT_DOUBLE_EQ(0, equals(a, e));
    };

    TEST(Complex, is_real){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {10.0, 0};
        const complex c = {0, 0};
        const complex d = {0, 5.0};
        
        EXPECT_DOUBLE_EQ(0, is_real(a));
        EXPECT_DOUBLE_EQ(1, is_real(b));
        EXPECT_DOUBLE_EQ(1, is_real(c));
        EXPECT_DOUBLE_EQ(0, is_real(d));
    };

    TEST(Complex, is_imaginary){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {10.0, 0};
        const complex c = {0, 0};
        const complex d = {0, 5.0};
        
        EXPECT_DOUBLE_EQ(0, is_imaginary(a));
        EXPECT_DOUBLE_EQ(0, is_imaginary(b));
        EXPECT_DOUBLE_EQ(1, is_imaginary(c));
        EXPECT_DOUBLE_EQ(1, is_imaginary(d));
    };

    TEST(Complex, is_zero){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {10.0, 0};
        const complex c = {0, 0};
        const complex d = {0, 5.0};
        
        EXPECT_DOUBLE_EQ(0, is_zero(a));
        EXPECT_DOUBLE_EQ(0, is_zero(b));
        EXPECT_DOUBLE_EQ(1, is_zero(c));
        EXPECT_DOUBLE_EQ(0, is_zero(d));
    };
}