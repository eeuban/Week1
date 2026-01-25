#include <stdio.h>
#include <math.h>
#include "complex.h"

// Adds two complex numbers together. Returns a complex number.
struct complex add(struct complex a, struct complex b){
    struct complex c;
    c.real = a.real + b.real;
    c.im = a.im + b.im;
    return c;
};

// // Adds subtracts complex numbers together. Returns a complex number.
// struct complex subtract(struct complex a, struct complex b){
//     struct complex c;
//     c.real = a.real - b.real;
//     c.im = a.im - b.im;
//     return c;
// };

// // Makes a complex number negaitve.
// struct complex negate(struct complex a){
//     struct complex c;
//     c.real = (-1)*a.real;
//     c.im = (-1)*a.im;
//     return c;
// };

// struct complex multiply(struct complex, struct complex);
// struct complex divide(struct complex, struct complex);
// struct complex conjugate(struct complex, struct complex);
// struct polar to_polar(struct complex, struct complex);
// struct complex power(struct complex, struct complex);
// // Magnitude for complex and polar number
// double magnitude_complex(struct complex);
// double magnitude_polar(struct polar);

// // Comparisons
// int equals(struct complex, struct complex);
// int is_real(struct complex, struct complex);
// int is_imaginary(struct complex);
// int is_zero(struct complex);


