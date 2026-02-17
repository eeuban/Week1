#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "gtest/gtest.h"
#include "matrix.h"

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

    TEST(Matrix, constructor){
        Matrix a;

        Matrix b({{1.0,2.0,3.0,4.0},{5.0,6.0,7.0,8.0},{9.0,10.0,11.0,12.0}});
        size_t num1 = 2, num2 = 2;
        printf("num of rows is %ld and num of cols is %ld\n", b.rows(), b.cols());
        printf("At index (%d, %d) value is: %f\n", 2, 2, b.at(num1, num2));

        Matrix c({{1.0,2.0,3.0,4.0},{5.0,6.0,7.0},{9.0,10.0,11.0,12.0}});

    }

    TEST(Matrix, Assignment){
        Matrix a;

        Matrix b({{1.0,2.0,3.0,4.0},{5.0,6.0,7.0,8.0},{9.0,10.0,11.0,12.0}});
        size_t num1 = 2, num2 = 2;

        a = b;
        printf("num of rows is %ld and num of cols is %ld\n", a.rows(), a.cols());
        printf("At index (%d, %d) value is: %f\n", 2, 2, a.at(num1, num2));
    }

    TEST(Matrix, Isempty){
        Matrix a;
        Matrix b({{1.0,2.0,3.0,4.0},{5.0,6.0,7.0,8.0},{9.0,10.0,11.0,12.0}});

        EXPECT_EQ(true, a.isEmpty());
        EXPECT_EQ(false, b.isEmpty());
    }

    TEST(Matrix, Issquare){
        Matrix a({{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}});
        Matrix b({{1.0,2.0,3.0,4.0},{5.0,6.0,7.0,8.0},{9.0,10.0,11.0,12.0}});

        EXPECT_EQ(true, a.isSquare());
        EXPECT_EQ(false, b.isSquare());
    }

    TEST(Matrix, Addition){
        Matrix a({{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}});
        Matrix b({{1.0,2.0,3.0},{5.0,6.0,7.0},{9.0,10.0,11.0}});

        Matrix c = a + b;
        
        std::cout << "a + b -> ";
        c.print();

        c += b;
        std::cout << "c += b -> ";
        c.print();
    }

    TEST(Matrix, subtraction){
        Matrix a({{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}});
        Matrix b({{1.0,2.0,3.0},{5.0,6.0,7.0},{9.0,10.0,11.0}});

        Matrix c = a - b;
        std::cout << "a - b -> ";
        c.print();

        c -= a;
        std::cout << "c -= b -> ";
        c.print();
    }

    TEST(Matrix, Multiplication){
        Matrix a({{1.0,2.0},{4.0,5.0},{7.0,8.0}});
        Matrix b({{1.0,2.0,3.0},{4.0,5.0,6.0}});

        Matrix c = a * b;
        std::cout << "a * b -> ";
        c.print();
    }

    TEST(Matrix, Scalar_Multiplication){
        Matrix a({{1.0,2.0},{4.0,5.0},{7.0,8.0}});

        Matrix c = a * 5;
        std::cout << "a * 5 -> ";
        c.print();

        c *= 5;
        std::cout << "c *= 5 -> ";
        c.print();

        c = 5 * a;
        std::cout << "5 * a -> ";
        c.print();
    }

    TEST(Matrix, Scalar_Division){
        Matrix a({{1.0,2.0},{4.0,5.0},{7.0,8.0}});

        Matrix c = a / 5;
        std::cout << "a / 5 -> ";
        c.print();

        c /= 5;
        std::cout << "c /= 5 -> ";
        c.print();

    }

    TEST(Matrix, Negation){
        Matrix a({{1.0,2.0},{4.0,5.0},{7.0,8.0}});

        Matrix c = -a;
        std::cout << "-a -> ";
        c.print();
    }

    TEST(Matrix, accessor){
        Matrix a({{1.0,2.0},{4.0,5.0},{7.0,8.0}});

        int num1 = 1, num2 = 1;
        std::cout << "At (" << num1 << ", " << \
        num2 << ") of matrix is " << a.at(num1, num2) << std::endl;

        std::cout << "At (" << num1 << ", " << \
        num2 << ") of matrix is " << a(num1, num2) << std::endl;

        a(num1,num2) = 6.0;
        a.print();
    }

    TEST(Matrix, equality){
        Matrix a({{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}});
        Matrix b({{1.0,2.0,3.0},{5.0,6.0,7.0},{9.0,10.0,11.0}});
        Matrix c({{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}});

        EXPECT_EQ( true, a==c );
        EXPECT_EQ( false, a==b );

        EXPECT_EQ(true, a!=b);
        EXPECT_EQ(false, a!=c);
    }

    TEST(Matrix, Identity){
        
        Matrix a;
        Matrix c = a.identity(5);

        c.print();
    }

    TEST(Matrix, zeros){
        
        Matrix a;
        Matrix c = a.zeros(3,5);

        Matrix d = a.zeros(1,5);

        c.print();
        d.print();
    }

    TEST(Matrix, ones){
        
        Matrix a;
        Matrix c = a.ones(3,5);

        Matrix d = a.ones(1,5);

        c.print();
        d.print();
    }

    TEST(Matrix, diagonal){
        
        Matrix a;
        std::vector<double> b{3,5,6,8};
        Matrix c = a.diagonal(b);

        std::vector<double> e{3,5,6,8,19.0,20.3,8.12};
        Matrix f = a.diagonal(e);

        c.print();
        f.print();
    }

    TEST(Matrix, Transpose){
        
        Matrix a({{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}});

        Matrix f = a.transpose();

        f.print();
    }

    TEST(Matrix, fill){
        
        Matrix a({{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}});

        a.fill(3.0);

        a.print();
    }

    TEST(Matrix, trace){
        
        Matrix a({{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}});

        EXPECT_EQ(15.0, a.trace());
    }

    TEST(Matrix, diagonalize){
        
        Matrix a({{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}});

        Matrix b = a.diagonal();

        b.print();
    }

    TEST(Matrix, norm){
        
        Matrix a({{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}});

        EXPECT_EQ(sqrt(285),a.norm());
    }

}