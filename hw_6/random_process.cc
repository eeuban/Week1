#include "elma/elma.h"
#include "random_process.h"
#include <random>

void RandomProcess::update(){
    channel("link").send(distrib(gen));
}

