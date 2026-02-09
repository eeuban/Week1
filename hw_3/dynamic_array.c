#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_new();
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }

  return result;

}

double DynamicArray_min(const DynamicArray * da){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) >= 1);

    int ptr = da->origin;
    double min = -__DBL_MAX__;
    while(ptr != da->end){
        if(DynamicArray_get(da, ptr) < min)
            min = DynamicArray_get(da, ptr);
        ptr++;
    }
    return min;
}

double DynamicArray_max(const DynamicArray * da){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) >= 1);

    int ptr = da->origin;
    double max = __DBL_MIN__;
    while(ptr != da->end){
        if(DynamicArray_get(da, ptr) > max)
            max = DynamicArray_get(da, ptr);
        ptr++;
    }
    return max;
}

double DynamicArray_mean(const DynamicArray * da){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) >= 1);

    int ptr = da->origin;
    double accumulate = 0;
    while(ptr != da->end){
        accumulate += DynamicArray_get(da, ptr);
        ptr++;
    }
    return accumulate / DynamicArray_size(da);
}

// Median is number that divides lower numbers with higher numbers
double DynamicArray_median(const DynamicArray * da){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) >= 1);
    
    DynamicArray * newary = DynamicArray_copy(da);
    DynamicArray_sort(newary);

    // If odd find middle value by dividing by 2. Else, find avg of middle values.
    if(DynamicArray_size(da) % 2 == 1){
        return DynamicArray_get(da, DynamicArray_size(da)/2);
    } else{
        double middleSum = DynamicArray_get(da, DynamicArray_size(da)/2) + DynamicArray_get(da, (DynamicArray_size(da)/2)-1);
        return middleSum / 2;
        
    }
}

void DynamicArray_sort(DynamicArray * da){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) >= 1);

    for(int z = 0; z < DynamicArray_size(da) - 1; z++){
        int swapped = 0;
        // Loop from origin to one before last value.
        for(int i = 0; i < DynamicArray_size(da) - z - 1; i++){
            if(DynamicArray_get(da, i+1) < DynamicArray_get(da, i)){
                double temp = DynamicArray_get(da, i);
                DynamicArray_set(da, i, DynamicArray_get(da, i+1));
                DynamicArray_set(da, i+1, temp);
                swapped = 1;
            }
        }
        if(!swapped)
            break;
    }
}

double DynamicArray_sum ( const DynamicArray * da ){
    assert(DynamicArray_size(da) >= 1);

    int frt = da->origin;
    double sum = 0;
    while(frt <= da->end){
        sum += DynamicArray_get(da, frt);
        frt++;
    }
    return sum;
}

double DynamicArray_first ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) >= 1);

    return DynamicArray_get(da, 0);
}

double DynamicArray_last ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) >= 1);

    return DynamicArray_get(da, DynamicArray_size(da)-1);
}

DynamicArray * DynamicArray_copy(const DynamicArray * da){

if(da->buffer == NULL)
    return DynamicArray_new();

DynamicArray * newda = DynamicArray_new();

for(int i = 0; i < DynamicArray_size(da); i++){
    DynamicArray_set(newda, i, DynamicArray_get(da, i));
}
return newda;
}

DynamicArray * DynamicArray_range(double start, double finish, double step){
    
    if(start == finish)
        return DynamicArray_new();
    if(fabs(step) > fabs(finish - start))
        return NULL;

    DynamicArray * da = DynamicArray_new();
    if (!da) return NULL;

    double currstep = start;
    if( start < finish){
        while(currstep <= finish){
            DynamicArray_push(da, currstep);
            currstep += fabs(step);
        }
    } else{
        while(currstep >= finish){
            DynamicArray_push(da, currstep);
            currstep -=fabs(step);
        }
    }
    return da;
}

DynamicArray * DynamicArray_concat (const DynamicArray * a, const DynamicArray * b){
    assert(a->buffer != NULL);
    assert(b->buffer != NULL);

    DynamicArray * newary = DynamicArray_new();

    for(int i = 0; i < DynamicArray_size(a); i++){
        DynamicArray_set(newary, i, DynamicArray_get(a, i));
    }
    for(int i = 0; i < DynamicArray_size(b); i++){
        DynamicArray_set(newary, DynamicArray_size(newary), DynamicArray_get(b, i));
    }

    return newary;
}

DynamicArray * DynamicArray_take(DynamicArray * a, int ammount){
    assert(a->buffer != NULL);
    DynamicArray * newary = DynamicArray_new();
    int to_take = abs(ammount);
    int left = 0;
    
    // Taking elements from back of old array.
    if(ammount < 0){
        
        // Number of 0's to fill if needed is greater than old array size.
        if(to_take > DynamicArray_size(a))
            left = to_take - DynamicArray_size(a);

        // Repeats until DynamicArray size. (to_take-left) keeps needed elements to take under size of array.
        for(int i = DynamicArray_size(a)-1; i > DynamicArray_size(a)-1-(to_take-left); i--)
            DynamicArray_set(newary, DynamicArray_size(a) - 1 - i, DynamicArray_get(a, i));
        
        // Fill in array with 0's
        while(left > 0){
            DynamicArray_set(newary, DynamicArray_size(newary), 0.0);
            left--;
        }
 
    }else{

        if(to_take > DynamicArray_size(a))
            left = DynamicArray_size(a) - to_take;

        for(int i = 0; i < to_take; i++){
            DynamicArray_set(newary, i, DynamicArray_get(a, i));
        }
        while(left > 0){
            DynamicArray_set(newary, DynamicArray_size(newary), 0.0);
            left--;
        }
    }
    return newary;
}

DynamicArray * DynamicArray_filter(const DynamicArray * a, int (*f)(double)){
    assert(a->buffer != NULL);
    
    DynamicArray * newary = DynamicArray_new();
    int decision = 0;
    for(int i = 0; i < DynamicArray_size(a); i++){
        double val = DynamicArray_get(a, i);
        decision = f(val);

        // If predicate returns values other than 1 or 0;
        if(decision != 1 && decision != 0){
            DynamicArray_destroy(newary);
            return NULL;
        }else if(decision)
            DynamicArray_set(newary, DynamicArray_size(newary), val);
        decision = 0;
    }
    return newary;
}

DynamicArray * DynamicArray_Unique(DynamicArray * a){
    if(a->buffer == NULL) return NULL;

    DynamicArray * unique = DynamicArray_new();

    // Loop through numbers and compare against unique array.
    for(int i = 0; i < DynamicArray_size(a); i++){
        int seen = 0;

        // Check for duplicates. If so set seen to restart loop
        for(int z = 0; z < DynamicArray_size(unique); z++){
            if(DynamicArray_get(a,i) == DynamicArray_get(a,z)) {
                seen=1;
                break;
            }
        }
        if(seen) continue;

        // Assign space to unique and store new element in unique.
        DynamicArray_set(unique, DynamicArray_size(unique), DynamicArray_get(a, i));
    }
    return unique;

}

DynamicArray ** DynamicArray_split(DynamicArray * a, int desired_chunks, int * actual_chunks){
    if(!a || !a->buffer) return NULL;
    if(desired_chunks <= 0) return NULL;
    if(!actual_chunks) return NULL;
    
    *actual_chunks = desired_chunks;
    int size = DynamicArray_size(a);
    int leftOver = size % desired_chunks;

    DynamicArray ** result = (DynamicArray **)malloc(*actual_chunks * sizeof(DynamicArray *));
    if(!result) return NULL;

    for(int i = 0; i < desired_chunks; i++){
        result[i] = DynamicArray_new();
        if(!result[i]){
            for(int j = 0; j < i;j++)
                DynamicArray_destroy(result[j]);
            free(result);
            return NULL;
        }
    }

    for(int i = 0; i < size; i++){
        int chunk = i % desired_chunks;
        DynamicArray_push(result[chunk], DynamicArray_get(a, i));
    }
    return result;
}