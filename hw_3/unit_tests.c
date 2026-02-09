#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {


    TEST(DynamicArray, sum){
        DynamicArray * a = DynamicArray_new();
        for(int i = 0; i < 10; i++){
            DynamicArray_push(a, (double)i+1);
        }
        printf("The sum of all elements in array is %f\n", DynamicArray_sum(a));

        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, median){
        DynamicArray * a = DynamicArray_new();

        DynamicArray_push(a, 1.0);
        DynamicArray_push(a, 2.0);
        DynamicArray_push(a, 3.0);
        DynamicArray_push(a, 4.0);
        DynamicArray_push(a, 5.0);

        ASSERT_EQ(DynamicArray_median(a), 3.0);
        DynamicArray_pop(a);
        ASSERT_EQ(DynamicArray_median(a), 2.5);
        DynamicArray_push(a, -3.0);
        //ASSERT_EQ(DynamicArray_median(a), 2.0);

        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, first){
        DynamicArray * a = DynamicArray_new();
        for(int i = 0; i < 10; i++){
            DynamicArray_push(a, (double)i+1);
        }
        DynamicArray_pop_front(a);

        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, last){
        DynamicArray * a = DynamicArray_new();
        for(int i = 0; i < 10; i++){
            DynamicArray_push(a, (double)i+1);
        }
        DynamicArray_pop_front(a);

        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, copy){
        DynamicArray * a = DynamicArray_new();

        for(int i = 0; i < 10; i++){
            DynamicArray_push(a, (double)i+1);
        }
        DynamicArray * newary = DynamicArray_copy(a);
        for(int i = 0; i < DynamicArray_size(newary); i++){
            ASSERT_EQ(DynamicArray_get(a, i), DynamicArray_get(newary, i));
        }
        
        DynamicArray_destroy(a);
        DynamicArray_destroy(newary);
    }

    TEST(DynamicArray, range){
        DynamicArray * da = DynamicArray_range(5, -3, -0.255678);
        printf("Returned array is %s\n", DynamicArray_to_string(da));

    }

    TEST(DynamicArray, concat){
        DynamicArray * a = DynamicArray_new();
        DynamicArray * b = DynamicArray_new();
        for(int i = 0; i < 10; i++){
            DynamicArray_push(a, (double)i+1);
            DynamicArray_push(b, (double)i+10);
        }
        DynamicArray * newary = DynamicArray_concat(a, b);
        printf("both array's combined are %s\n", DynamicArray_to_string(newary));
    }

    TEST(DynamicArray, take){
        DynamicArray * a = DynamicArray_new();
        for(int i = 0; i < 10; i++) DynamicArray_push(a, (double)i+1);

        DynamicArray * newary = DynamicArray_take(a, 1);
        DynamicArray * newary1 = DynamicArray_take(a, 5);
        DynamicArray * newary2 = DynamicArray_take(a, 10);
        DynamicArray * newary3 = DynamicArray_take(a, -1);
        DynamicArray * newary4 = DynamicArray_take(a, -10);
        DynamicArray * newary5 = DynamicArray_take(a, -15);
        printf("Array after take is %s\n", DynamicArray_to_string(newary));
    }

    TEST(DynamicArray, filter){
        DynamicArray * a = DynamicArray_new();
        DynamicArray_push(a, 1.0);
        DynamicArray_push(a, 3.0);
        DynamicArray_push(a, -2.0);
        DynamicArray_push(a, 10.0);
        DynamicArray_push(a, -23.0);

        int ( *isPositive)(double) = [](double a){if (a >= 0) return 1; else return 0;};
        int ( *between0and10)(double) = [](double a){if (a >= 0 && a < 10) return 1; else return 0;};
        DynamicArray * newary = DynamicArray_filter(a, isPositive);
        DynamicArray * newary1 = DynamicArray_filter(a, between0and10);
    }

    TEST(DynamicArray, unique){
        DynamicArray * a = DynamicArray_new();
        DynamicArray_push(a, 1.0);
        DynamicArray_push(a, 3.0);
        DynamicArray_push(a, -2.0);
        DynamicArray_push(a, 10.0);
        DynamicArray_push(a, -23.0);

        DynamicArray * newary = DynamicArray_Unique(a);

        DynamicArray_push(a, -23.0);
        DynamicArray_push(a, -23.0);
        DynamicArray_push(a, -23.0);

        DynamicArray * newary1 = DynamicArray_Unique(a);
    }

    TEST(DynamicArray, split){
        DynamicArray * a = DynamicArray_new();
        DynamicArray_push(a, 1.0);
        DynamicArray_push(a, 3.0);
        DynamicArray_push(a, -2.0);
        DynamicArray_push(a, 10.0);
        DynamicArray_push(a, -23.0);

        int actualchunks = 0;
        DynamicArray ** chunks = DynamicArray_split(a, 2, &actualchunks);
        for(int i = 0; i < actualchunks; i++){
            printf("Array %d is %s\n", i, DynamicArray_to_string(chunks[i]));
        }
    }

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }

}