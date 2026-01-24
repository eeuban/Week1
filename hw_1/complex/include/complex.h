#include <stdio.h>

struct complex{
    double real;
    double im;
} complex;

struct polar{
    double r;
    double theta;
} polar;

// Basic Operators
struct complex add(struct complex, struct complex);
struct complex subtract(struct complex, struct complex);
struct complex negate(struct complex, struct complex);
struct complex multiply(struct complex, struct complex);
struct complex divide(struct complex, struct complex);
struct complex conjugate(struct complex, struct complex);
struct polar to_polar(struct complex, struct complex);
struct complex power(struct complex, struct complex);
// Magnitude for complex and polar number
double magnitude_complex(struct complex);
double magnitude_polar(struct polar);

// Comparisons
int equals(struct complex, struct complex);
int is_real(struct complex, struct complex);
int is_imaginary(struct complex);
int is_zero(struct complex);