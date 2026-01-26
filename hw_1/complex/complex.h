#ifndef _COMPLEX
#define _COMPLEX

#include <stdio.h>

typedef struct {
    double real;
    double im;
} complex;

typedef struct {
    double r;
    double theta;
} polar;

// Basic Operators
complex add(complex a, complex b);
complex subtract(complex a, complex b);
complex negate(complex a);
complex multiply(complex a, complex b);
complex divide(complex a, complex b);
complex conjugate(complex a);
polar to_polar(complex a);
complex power(complex a, int b);
double magnitude(complex a);

// Comparisons
int equals(complex a, complex b);
int is_real(complex a);
int is_imaginary(complex a);
int is_zero(complex a);

// Auxilliary
int Is_Infinite(complex a);
int willOverflow(double a, double b);

#endif