#include "elma/elma.h"
#include "Integrator.h"
#include <iostream>

double Integrator::value(){
    double v = channel("link").latest();
    return delta() * v;
}

void Integrator::update(){
    if(channel("link").nonempty())
        accumulate += value();
}