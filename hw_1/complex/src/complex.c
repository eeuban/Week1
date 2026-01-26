/* Used chatGPT model GPT-5.2 to understand floating point arithmetic and IEEE 754 handeling of 
high magnitude Arithmetic.*/

#include <stdio.h>
#include <math.h>
#include "complex.h"
#include <float.h>

// Test if a complex number is infinite. Returns 1 if infinite and 0 if not.
int is_infinite(complex a){
    if((a.real == INFINITY)||(a.im == INFINITY)||(a.real == -INFINITY)||(a.im == -INFINITY))
       return 1;
    else
        return 0;
};

// Checks if Overflow will occur before multiply operation. If a * b > DBL_MAX then operation will overflow.
// We check if the a is a number greater than quotient DBL_MAX / b. Returns 1 if the operation will overflow
// and 0 if not.
int willOverflow(double a, double b){
    if(a > 0 && b > 0 && a > DBL_MAX / b) return 1;
    if(a > 0 && b > 0 && b > DBL_MAX / a) return 1;
    return 0;
};

// Adds two complex numbers together. Returns a complex number. The real and imaginary parts will be -1.0 if 
// The sum aproaches Infinity.
 complex add(complex a, complex b){
    complex c;
    // If real or im part is INFINIFY Then return -1.0. With negatives Vice Versa.
    if(is_infinite(a)||is_infinite(b)){
        c.real = -1.0;
        c.im = -1.0;
        return c;
    }
    c.real = a.real + b.real;
    c.im = a.im + b.im;

    return c;
};

// Adds subtracts complex numbers together. Returns a complex number. The real and imaginary parts will be
// -1.0 if the values include numbers close to infinity.
 complex subtract(complex a,  complex b){
    complex c;
    if(is_infinite(a)||is_infinite(b)){
        c.real = -1.0;
        c.im = -1.0;
        return c;
    }
    c.real = a.real - b.real;
    c.im = a.im - b.im;
    return c;
};

// Makes a complex number negaitve.  The real and imaginary parts will be -1.0 if the values include numbers 
// close to infinity.
 complex negate(complex a){
    complex c;
    if(is_infinite(a)){
        c.real = -1.0;
        c.im = -1.0;
        return c;
    }
    c.real = (-1)*a.real;
    c.im = (-1)*a.im;
    return c;
};

// Multiply complex number a by complex number b. A complex number is returned. The real and imaginary parts will be
// -1.0 if the values include numbers close to infinity. -1.0 for each part will also be returned if product is 
// determined to overflow.
complex multiply(complex a, complex b){
    complex c;
    if(is_infinite(a)||is_infinite(b)){
        c.real = -1.0;
        c.im = -1.0;
        return c;
    }

    // returns -1.0 if product is too large.
    if(willOverflow(a.real, b.real)||willOverflow(a.im, b.im)){
        c.real = -1.0;
        c.im = -1.0;
    }

    c.real = a.real * b.real;
    c.im = a.im * b.im;
    return c;
};

// Divides complex number a by complex number b. If b is zero, Infinity is returned for both real and imaginary 
// parts. A complex number is returned. The real and imaginary parts will be -1.0 if the values include numbers 
// close to infinity. -1.0 for each part will also be returned if product is determined to overflow.
complex divide(complex a, complex b){
    complex c;
    if(is_infinite(a)||is_infinite(b)){
        c.real = -1.0;
        c.im = -1.0;
        return c;
    }

    // Here we process Infinities when zeros are introduced.
    if (b.real == 0.0 || b.im == 0.0){
        c.real = INFINITY;
        c.im = INFINITY;
        return c;
    }

    if(willOverflow(a.real, b.real)||willOverflow(a.im, b.im)){
        c.real = -1.0;
        c.im = -1.0;
        return c;
    }

    c.real = a.real / b.real;
    c.im = a.im / b.im;
    return c;
};

// Returns conjugate of complex number. Multiply imaginary number by -1 to negate the number. The real and imaginary parts will be
// -1.0 if the values include numbers close to infinity.
complex conjugate(complex a){
    complex c;
    if(is_infinite(a)){
        c.real = -1.0;
        c.im = -1.0;
        return c;
    }
    c = {a.real, (-1)*a.im};
    return c;
};

// Converts complex number to polar number. Compute magnitude and angle of complex number using euclidean distance 
// and arctan respectively. A Polar number is returned. The magnitude will be -1.0 and theta will be if -7.0 the values
// include numbers close to infinity. -1.0 and -7.0 will also be used to determine overflow. Maximum and minimum values
// for theta include -6.283 radians to 6.283 radians (2pi).
polar to_polar(complex a){
    polar c;
    if(is_infinite(a)){
        c.r = -1.0;
        c.theta = -7.0;
        return c;
    }

    // Prevent power for overflowing
    if(willOverflow(a.real, a.real)||willOverflow(a.im, a.im)){
        c.r = -1.0;
        c.theta = -7.0;
        return c;
    }

    double r = sqrt(pow(a.real, 2) + pow(a.im, 2));
    double theta = atan2(a.im, a.real);

    // If theta is greater than circumfrance of a circle, return as undefined behavior.
    if (theta > 2 * M_PI || theta < 2 * M_PI){
        c.r = -1.0;
        c.theta = -7.0;
    }
    c = {r, theta};
    return c;
};

// Takes complex number a to the power of b. Returns a complex number. The real and imaginary parts will be -1.0 if the values include numbers 
// close to infinity. -1.0 for each part will also be returned if product is determined to overflow.
complex power(complex a, int b){
    complex c;
    if(is_infinite(a)){
        c.real = -1.0;
        c.im = -1.0;
        return c;
    }

    double realpwr = 1.0, imgpwr = 1.0;
    for(int i = 0; i < abs(b); i++){
        // Checks if multipication will overflow before multiply.
        if(willOverflow(realpwr, a.real)||willOverflow(imgpwr, a.im)){
            c.real = -1.0;
            c.im = -1.0;
            return c;
        }
        realpwr *= a.real;
        imgpwr *= a.im;
    }

    if (b < 0)
        c = {1/realpwr, 1/imgpwr};
    else
        c = {realpwr, imgpwr};
    
    return c;
};

// Magnitude for complex number. A double is returned. -1.0 will be returned if the values include numbers 
// close to infinity. -1.0 will also be returned if possible overflow.
double magnitude(complex a){
    complex c;
    if(is_infinite(a))
        return -1.0;

    // Prevents power if product is too large.
    if(willOverflow(a.real, a.real)||willOverflow(a.im, a.im))
        return -1.0;

    return sqrt(pow(a.real, 2) + pow(a.im, 2));
};

// Comparisons
// We also check Infinities with comparision operators. When comparing infinities C determines math weirdly.
// Ex. INFINITY - 1 == INFINITY. While not equal they are determined equal in C. Will check for Infinity prior.

// Determines if complex number a is equal to b. Returns 1 for true and 0 for false. -1.0 will also be returned 
// if Infinite values are used.
int equals(complex a, complex b){
    complex c;
    if(is_infinite(a)||is_infinite(b))
        return -1;

    if((a.real == b.real)&&(a.im == b.im)){
        return 1;
    }
    return 0;
}

// If imaginary part is 0, the number is real. Return 1 if real, 0 if not. -1.0 will also be returned 
// if Infinite values are used.
int is_real(complex a){
    complex c;
    if(is_infinite(a))
        return -1;

    if(a.im == 0.0){
        return 1;
    }
    return 0;
}

// Checks if number is imaginary. If real part is zero. Return 1 if imaginary, 0 if not. -1.0 will also be returned 
// if Infinite values are used.
int is_imaginary(complex a){
    complex c;
    if(is_infinite(a))
        return -1;

    if(a.real == 0.0){
        return 1;
    }
    return 0;
};

// Check if both parts are zero. If both real and imaginary parts are zero, return 1. If any one is not zero return 0.
// -1.0 will also be returned if infinite values are used.
int is_zero(complex a){
    complex c;
    if(is_infinite(a))
        return -1;

    if((a.real == 0.0)&&(a.im == 0.0)){
        return 1;
    }
    return 0;
};