#include "complex.h"
#include "math.h"
#include "gtest/gtest.h"

namespace{

    TEST(Complex, add){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {22.0, 4.0};

        const complex c = add(a, b);

        EXPECT_DOUBLE_EQ(c.real, 32.0);
        EXPECT_DOUBLE_EQ(c.im, 9.0);
    };

    TEST(Complex, subtract){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {22.0, 4.0};

        const complex c = subtract(a, b);

        EXPECT_DOUBLE_EQ(c.real, -12.0);
        EXPECT_DOUBLE_EQ(c.im, 1);
    };

    TEST(Complex, multiply){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {22.0, 4.0};

        const complex c = multiply(a, b);

        EXPECT_DOUBLE_EQ(c.real, 220.0);
        EXPECT_DOUBLE_EQ(c.im, 20.0);
    };

    TEST(Complex, divide){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {22.0, 4.0};
        const complex azero = {0., 5.0};
        const complex bzero = {.6, 0.};

        const complex c = divide(a, b);
        const complex c1 = divide(azero, b);
        const complex c2 = divide(a, bzero);

        EXPECT_DOUBLE_EQ(c.real, 10.0/22.0);
        EXPECT_DOUBLE_EQ(c.im, 1.25);

        EXPECT_DOUBLE_EQ(c1.real, 0);
        EXPECT_DOUBLE_EQ(c1.im, 5/4.0);

        EXPECT_DOUBLE_EQ(c2.real, INFINITY);
        EXPECT_DOUBLE_EQ(c2.im, INFINITY);
    };

    TEST(Complex, conjugate){
        // Vars
        const complex a = {10.0, 5.0};
        
        const complex actual = conjugate(a);
        EXPECT_DOUBLE_EQ(actual.real, a.real);
        EXPECT_DOUBLE_EQ(actual.im, -5.0);
    };

    TEST(Complex, 2polar){
        // Vars
        const complex a = {10.0, 5.0};
        
        const polar actual = to_polar(a);
        EXPECT_DOUBLE_EQ(actual.r, 5*sqrt(5));
        EXPECT_DOUBLE_EQ(actual.theta, atan2(5.0, 10.0));
    };

    TEST(Complex, power){
        // Vars
        const complex a = {10.0, 5.0};
        
        const complex actual = power(a, 2);
        EXPECT_DOUBLE_EQ(actual.real, 100.0);
        EXPECT_DOUBLE_EQ(actual.im, 25.0);
    };

    TEST(Complex, magnitude){
        // Vars
        const complex a = {10.0, 5.0};
        
        double actual = magnitude(a);
        EXPECT_DOUBLE_EQ(actual, 5*sqrt(5));
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