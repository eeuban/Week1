#include "complex.h"
#include "gtest/gtest.h"

namespace{
        struct complex a = {(double)10.f, (double)5.f};
        struct complex b = {(double)22.f, (double)4.f};

    TEST(Complex, add){
        struct complex c = {(double)32.f,(double)9.f};
        struct complex d = add(a, b);
        EXPECT_EQ(c.real, d.real);
        EXPECT_EQ(c.im, d.im);
    };

}