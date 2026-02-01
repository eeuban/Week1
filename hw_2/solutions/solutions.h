#ifndef SOLUTIONS
#define SOLUTIONS

#include <stdio.h>

/*! Tracks the sum of the arguments given over time.
 *  \param a Given value
 */
int running_total(int a);

/*! Takes an array and its length and returns a new array that is the reverse of given one.
 *  \param array Array given
 *  \param size Size of Array
 */
int * reverse(int * array, int size);

/*! Takes an array and its length and reverse in given array.
 *  \param array Array given
 *  \param size Size of Array
 */
void reverse_in_place(int * array, int size);

/*! Takes an array, its length and wanted number and returns number of occurances of number.
 *  \param array Array given
 *  \param size Size of Array
 *  \param num number to search for
 */
int num_occurences(int * array, int size, int num);

/*! Takes an array, its length, and new length. A new array will be returned containing 
 *only new elements.
 *  \param array Array given
 *  \param size Size of Array
 *  \param newlen New array size
 */
int * remove_duplicates(int * array, int size, int * newlen);

/*! Takes C-string, Returns a new C-string that is reversed. If NULL is given return NULL.
 *  \param str string given
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