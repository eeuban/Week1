#include <stdio.h>
#include <stdlib.h>
#include "solutions.h"
#include <string.h>

/**
 * @addtogroup arrayOperations
 * @{
 */

int running_total (int a){
    static int total;
    return total += a;
}

int * reverse(int * array, int size){
    
    if(array == NULL || size <= 0) return NULL;
    int * ptr = (int *)calloc(size, sizeof(int));
    if(ptr == NULL) return NULL;

    int i = 0;
    int z = size-1;

    while(z >= 0){
        ptr[i] = array[z];
        i++;
        z--;
    }

    return ptr;
}

void reverse_in_place(int * array, int size){

    if(array == NULL || size <= 0) return;

    for(int i = 0; i < size/2; i++){
        int temp = array[size-1 - i];
        array[size-1 - i] = array[i];
        array[i] = temp;
    }
}

int num_occurences(int * array, int size, int num){

    if(array == NULL || size <= 0) return NULL;

    int occur = 0;
    for(int i = 0; i < size; i++){
        if( num == array[i])
            occur++;
    }
    return occur;
}

int * remove_duplicates(int * array, int size, int * newlen){

    if(array == NULL || size <= 0) return NULL;

    int * unique = NULL;
    *newlen = 0;

    // Loop through numbers and compare against unique array.
    for(int i = 0; i < size; i++){
        int seen = 0;

        // Check for duplicates. If so set seen to restart loop
        for(int z = 0; z < *newlen; z++){
            if(array[i] == unique[z]) {
                seen=1;
                break;
            }
        }

        if(seen) continue;

        // Allocate extra space for incoming element.
        int * temp = (int*) realloc(unique,(*newlen+1) * sizeof(int));
        if(!temp){
            free(unique);
            return NULL;
        }

        // Assign space to unique and store new element in unique.
        unique = temp;
        unique[*newlen] = array[i];
        (*newlen)++;

    }
    return unique;
}

/** @} */ // end of arrayOperations

/**
 * @addtogroup stringOperations
 * @{
 */

char * string_reverse(char * str){

    if(str == NULL) return NULL;

    char * result;
    int len = 0;
    while(str[len] != '\0') len++;

    result = (char *) malloc(len * sizeof(char));

    for(int i = 0; i < len; i++){
        result[i] = str[len - 1 - i];
    }
    result[len] = '\0';

    return result;
}

int * transpose(int * matrix, int row, int col){

    if(matrix == NULL || row <= 0 || col <= 0) return NULL;

    int expected_ele = 0;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            expected_ele++;
        }
    }

    // Checks if given dimensions are correct.
    if(row * col != expected_ele ) return NULL;

    int * newmatrix = (int *)malloc((row * col) * sizeof(int));

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++)
            newmatrix[j * row + i] = matrix[i * col + j];
    }

    return newmatrix;
}

char ** split_string(char * str, char c , int * count){

if (!str || !count ) return NULL;

    int num_of_strs = 0, resultlen = 0, initial = 0, strlen = 0;
    char **result = NULL;

    for (int i = 0; ; i++){

        // If str isn't a  delimiter or '\0' increase string length and continue loop.
        if (str[i] != c && str[i] != '\0'){
            strlen++;
            continue;
        }

        // Allocate string with string length size + 1 for '\0'.
        char *temp = (char *) malloc((strlen + 1) * sizeof *temp);
        if (!temp) return NULL;

        // Store current string in new string space.
        for (int z = 0; z < strlen; z++)
            temp[z] = str[initial + z];

        temp[strlen] = '\0';

        // Allocate space for ptr to point to new strings.
        char **tmp = (char **)realloc(result, (num_of_strs + 1) * sizeof *result);
        if (!tmp) return NULL;
        result = tmp;

        // Store temp in result.
        result[num_of_strs++] = temp;

        if (str[i] == '\0')
            break;

        initial = i + 1;
        strlen = 0;
    }

    *count = num_of_strs;
    return result;

}

void free_string_array(char **result, int & count){
    for(int i = 0; i < count; i++){
        free(result[i]);
    }
}

/** @} */ // end of stringOperations