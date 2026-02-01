#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "solutions.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    TEST(solutions, running_total){
        ASSERT_EQ(running_total(1), 1);
        ASSERT_EQ(running_total(1), 2);
        ASSERT_EQ(running_total(5), 7);
        ASSERT_EQ(running_total(-3), 4);
    }

    TEST(solutions, reverse){
        int x[] = {10,20,30,40,50};
        int * y = reverse(x, 5);
        ASSERT_EQ(y[0],50);
        ASSERT_EQ(y[1],40);
        ASSERT_EQ(y[2],30);
        ASSERT_EQ(y[3],20);
        ASSERT_EQ(y[4],10);
        free(y);

        int * z = reverse(x, -1);
        ASSERT_EQ(z, nullptr);
        free(z);

    }

    TEST(HW2,ReverseInPlace){
        int x[] = {10,20,30,40,50};
        reverse_in_place(x,5);
        ASSERT_EQ(x[0],50);
        ASSERT_EQ(x[1],40);
        ASSERT_EQ(x[2],30);
        ASSERT_EQ(x[3],20);
        ASSERT_EQ(x[4],10);
    }

    TEST(HW2,NumInstances){
        int a[] = { 1, 1, 2, 3, 1, 4, 5, 2, 20, 5 };
        ASSERT_EQ(num_occurences(a,10,1), 3);
    }

    TEST(HW2, RemoveDuplicates) {
        int a[] = {1, 2, 2, 3, 1, 4, 5, 2};
        int new_len;
        int *result = remove_duplicates(a, 8, &new_len);
        ASSERT_EQ(new_len, 5);
        ASSERT_EQ(result[0], 1);
        ASSERT_EQ(result[1], 2);
        ASSERT_EQ(result[2], 3);
        ASSERT_EQ(result[3], 4);
        ASSERT_EQ(result[4], 5);
        free(result);
    }

    TEST(HW2, StringReverse) {
        char *result = string_reverse("hello");
        ASSERT_STREQ(result, "olleh");
        free(result);
    }
   
    TEST(HW2, Transpose) {
        // 2x3 matrix: [[1,2,3], [4,5,6]]
        int matrix[] = {1, 2, 3, 4, 5, 6};
        int *result = transpose(matrix, 2, 3);
        // Expected 3x2: [[1,4], [2,5], [3,6]]
        int expected[] = {1, 4, 2, 5, 3, 6};
        for (int i = 0; i < 6; i++) {
            ASSERT_EQ(result[i], expected[i]);
        }
        free(result);
    }

    TEST(HW2, SplitString) {
        int count;
        char **result = split_string("apple,banana,cherry", ',', &count);
        ASSERT_EQ(count, 3);
        ASSERT_STREQ(result[0], "apple");
        ASSERT_STREQ(result[1], "banana");
        ASSERT_STREQ(result[2], "cherry");
        free_string_array(result, count);

        result = split_string("apple,banana,cherry", 'a', &count);
        ASSERT_EQ(count, 5);
        ASSERT_STREQ(result[0], "");
        ASSERT_STREQ(result[1], "pple,b");
        ASSERT_STREQ(result[2], "n");
        ASSERT_STREQ(result[3], "n");
        ASSERT_STREQ(result[4], ",cherry");
        free_string_array(result, count);
    }

}