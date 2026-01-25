#include <stdio.h>
#include <math.h>
#include "complex.h"

// Adds two complex numbers together. Returns a complex number.
 complex add(complex a, complex b){
    complex c;
    c.real = a.real + b.real;
    c.im = a.im + b.im;
    return c;
};

// Adds subtracts complex numbers together. Returns a complex number.
 complex subtract(complex a,  complex b){
    complex c;
    c.real = a.real - b.real;
    c.im = a.im - b.im;
    return c;
};

// Makes a complex number negaitve.
 complex negate(complex a){
    complex c;
    c.real = (-1)*a.real;
    c.im = (-1)*a.im;
    return c;
};

// Multiply complex number a by complex number b. A complex number is returned. 
complex multiply(complex a, complex b){
    complex c;
    c.real = a.real * b.real;
    c.im = a.im * b.im;
    return c;
};

// Divides complex number a by complex number b. If b is zero, Infinity is returned for both
// real and imaginary parts. A complex number is returned. 
complex divide(complex a, complex b){
    complex c;
    if (b.real == 0.0 || b.im == 0.0){
        c.real = INFINITY;
        c.im = INFINITY;
        return c;
    }
    c.real = a.real / b.real;
    c.im = a.im / b.im;
    return c;
};

// Returns conjugate of complex number. Multiply imaginary number by -1 to negate the number.
complex conjugate(complex a){
    complex c = {a.real, (-1)*a.im};
    return c;
};

// Converts complex number to polar number. Compute magnitude and angle of complex number
// using euclidean distance and arctan respectively. A Polar number is returned.
polar to_polar(complex a){
    double r = sqrt(pow(a.real, 2) + pow(a.im, 2));
    double theta = atan2(a.im, a.real);              
    polar c = {r, theta};

    return c;
};

complex power(complex a, int b){
    double realpwr = 1.0, imgpwr = 1.0;
    for(int i = 0; i < b; i++){
        realpwr *= a.real;
        imgpwr *= a.im;
    }
    complex c = {realpwr, imgpwr};
    return c;
};
// Magnitude for complex and polar number
double magnitude_complex( complex);
double magnitude_polar( polar);

// Comparisons
int equals( complex,  complex);
int is_real( complex,  complex);
int is_imaginary( complex);
int is_zero( complex);


