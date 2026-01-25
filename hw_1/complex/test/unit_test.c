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
        const complex b = {22.0, 4.0};
        
        const complex actual = conjugate(a);
        EXPECT_DOUBLE_EQ(actual.real, a.real);
        EXPECT_DOUBLE_EQ(actual.im, -5.0);
    };

    TEST(Complex, 2polar){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {22.0, 4.0};
        
        const polar actual = to_polar(a);
        EXPECT_DOUBLE_EQ(actual.r, 5*sqrt(5));
        EXPECT_DOUBLE_EQ(actual.theta, atan2(5.0, 10.0));
    };

    TEST(Complex, power){
        // Vars
        const complex a = {10.0, 5.0};
        const complex b = {22.0, 4.0};
        
        const complex actual = power(a, 2);
        EXPECT_DOUBLE_EQ(actual.real, 100.0);
        EXPECT_DOUBLE_EQ(actual.im, 25.0);
    };

}