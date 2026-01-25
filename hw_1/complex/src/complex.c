/* Used chatGPT model 3 to understand how floating point IEEE 754 standard handles highmagnitudes subtracted by smaller ones.*/

#include <stdio.h>
#include <math.h>
#include "complex.h"

// Adds two complex numbers together. Returns a complex number.
 complex add(complex a, complex b){
    complex c;

    // If real or im part is greater than maximum double subtracted by second complex number
    // Then return -1.0. With negatives Vice Versa.
    if((a.real > __DBL_MAX__ - b.real)||(c.im > __DBL_MAX__ - b.im)||
       (a.real < nextafter(-INFINITY,b.real))||(a.im < nextafter(-INFINITY,b.im))){

        c.real = -1.0;
        c.im = -1.0;
        return c;
    }
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

// Magnitude for complex number. A double is returned.
double magnitude(complex a){
    return sqrt(pow(a.real, 2) + pow(a.im, 2));
};

// Comparisons
// Determines if complex number a is equal to b. Returns 1 for true and 0 for false.
int equals(complex a, complex b){
    if((a.real == b.real)&&(a.im == b.im)){
        return 1;
    }
    return 0;
}

// If imaginary part is 0, the number is real. Return 1 if real, 0 if not.
int is_real(complex a){
    if(a.im == 0.0){
        return 1;
    }
    return 0;
}

// Checks if number is imaginary. If real part is zero. Return 1 if imaginary, 0 if not.
int is_imaginary(complex a){
    if(a.real == 0.0){
        return 1;
    }
    return 0;
};

// Check if both parts are zero. If both real and imaginary parts are zero, return 1. If
// any one is not zero return 0.
int is_zero(complex a){
    if((a.real == 0.0)&&(a.im == 0.0)){
        return 1;
    }
    return 0;
};


