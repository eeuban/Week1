#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "gtest/gtest.h"

namespace {

    TEST(TypedArray, Construction) {
        TypedArray<int> b;
        b.set(0, 1);
        b.set(1, 2);
        b.set(20, 3);
        EXPECT_EQ(b.get(0), 1);
        EXPECT_EQ(b.get(1), 2);
        EXPECT_EQ(b.get(20), 3);
    }

    TEST(TypedArray, Defaults) {
        TypedArray<int> x;
        int& y = x.get(4);
        std::cout << x << "\n";
        EXPECT_EQ(y, 0);
    }

    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }

    TEST(TypedArray,CopyElementsInSet1) {
        TypedArray<int> b;
        int five = 5;
        b.set(0, five);
        five = 4;
        EXPECT_DOUBLE_EQ(b.get(0), 5);
    }

    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    }

    TEST(TypedArray, push) {
        TypedArray<int> a;
        a.push(1);
        a.push(2);
        a.push(3);
        for(int i = 0; i < a.size(); i++) EXPECT_EQ(a.get(i), i+1);
    }

    TEST(TypedArray, pushfront) {
        TypedArray<int> a;
        a.pushfront(1);
        a.pushfront(2);
        a.pushfront(3);
        for(int i = 0; i < a.size(); i++) EXPECT_EQ(a.get(a.size() - 1 - i), i+1);
    }

    TEST(TypedArray, pop) {
        TypedArray<int> a;
        a.push(1);
        a.push(2);
        a.push(3);
        EXPECT_EQ(a.pop(), 3);
    }

    TEST(TypedArray, popfront) {
        TypedArray<int> a;
        a.push(1);
        a.push(2);
        a.push(3);
        EXPECT_EQ(a.popfront(), 1);
    }

    TEST(TypedArray, concatenate){
        TypedArray<int> a;
        a.push(1);
        a.push(2);
        a.push(3);

        TypedArray<int> b;
        b.push(4);
        b.push(5);

        TypedArray<int> c = a.concat(b);
        std::cout << "array a is: " << \
         a << std::endl << "array b is: " << \
         b << std::endl <<"concatenated array c is: " << c << std::endl;

        TypedArray<int> d = c.concat(a);
        std::cout << "array c concatenated with a is: " << d << std::endl;

    }

    TEST(TypedArray, reverse){
        TypedArray<int> a;
        a.push(1);
        a.push(2);
        a.push(3);
        a.push(4);
        a.push(5);

        std::cout << "Original array is " << a << std::endl;

        TypedArray<int> reverseda = a.reverse();
        std::cout << "Reversed array is " << reverseda << std::endl;
    }

        TEST(TypedArray, plus){
        TypedArray<int> a;
        a.push(1);
        a.push(2);
        a.push(3);

        TypedArray<int> b;
        b.push(4);
        b.push(5);

        TypedArray<int> c = a + b;
        std::cout << "array a is: " << \
         a << std::endl << "array b is: " << \
         b << std::endl <<"concatenated array c is: " << c << std::endl;

        TypedArray<int> d = c + a;
        std::cout << "array c concatenated with a is: " << d << std::endl;

    }
}