/**
 * @file solutions.h
 * @brief Definition of function prototypes for array and string operations.
 * @details Provides function prototypes for functions reversing array, summing
 * array, removing of duplicates, transposition, and more.
 *
 * - @subpage arrayOperations
 * - @subpage stringOperations
*/


#ifndef SOLUTIONS
#define SOLUTIONS

#include <stdio.h>

/**
 *@addtogroup arrayOperations
 *@{
 * 
*/

/**
 * @brief Tracks the sum of the arguments given over time.
 * @param a Given value
 * @return Sum of provided arguments.
 */
int running_total(int a);

/**
 * @brief Takes an array and its length and returns a new array that is the reverse of given one.
 * @param array Array given.
 * @param size Size of Array.
 * @return Array that has elements reversed.
 */
int * reverse(int * array, int size);

/**
 * @brief an array and its length and reverse in given array.
 * @param array Array given.
 * @param size Size of Array.
 * @return Nothing is returned.
 */
void reverse_in_place(int * array, int size);

/**
 * @brief Takes an array, its length and wanted number and returns number of occurances of number.
 * @param array Array given.
 * @param size Size of Array.
 * @param num Number to search for.
 * @return Occurence of searched number in Array.
 */
int num_occurences(int * array, int size, int num);

/**
 * @brief Takes an array, its length, and new length. A new array will be returned containing 
 * only new elements.
 * @param Array given.
 * @param Size of Array.
 * @param Newlen New array size.
 * @return A new array with duplicates removed.
 */
int * remove_duplicates(int * array, int size, int * newlen);

/**
 * 
 * @brief Takes C-string, Returns a new C-string that is reversed. If NULL is given return NULL.
 * @param str string given
 */
char * string_reverse(char * str);

/*! Takes matrix in row-major order and returns its transpose.
 *  \param matrix array given
 *  \param row row of matrix
 *  \param col column of matrix
 */
int * transpose(int * matrix, int row, int col);

/*! Takes A string divides into multiple new strings by delimiter. Updates count with number of 
 * strings returned.
 *  \param str original string
 *  \param c delimiter
 *  \param count number of strings returned
 */
char ** split_string(char * str, char c , int * count);

/*! Deallocates str pointer.
 *  \param str original string
 *  \param count number of strings returned
 */
void free_string_array(char **result, int & count);

#endif