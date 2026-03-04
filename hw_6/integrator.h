#include <iostream>
#include "elma/elma.h"
#include <string>

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

class Integrator : public elma::Process{
public:
    Integrator(std::string name) : Process(name), accumulate(0.0){}

    void init(){}
    void start(){}
    void stop(){}
    void update();

    double value();

private:
    double accumulate;
};


#endif