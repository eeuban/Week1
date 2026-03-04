#include <iostream>
#include "elma/elma.h"
#include <deque>

#ifndef FILTER_H
#define FILTER_H

class Filter : public elma::Process{
public:
    Filter(std::string name) : Process(name){}

    void init(){};
    void start(){};
    void update();
    void stop(){};

    double value();

private:
    std::deque<double> nums;
};

#endif