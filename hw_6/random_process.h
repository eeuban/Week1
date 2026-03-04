#ifndef RANDOMPROCESS_H
#define RANDOMPROCESS_H

#include "elma/elma.h"
#include <random>

class RandomProcess : public elma::Process {
public:
    RandomProcess(std::string name)
    : elma::Process(name),
        gen(std::random_device{}()),
        distrib(0.0, 1.0)
    {}

    void init() {}
    void start() {}
    void update();
    void stop() {}

private:
    std::mt19937 gen;
    std::uniform_real_distribution<double> distrib;
};

#endif