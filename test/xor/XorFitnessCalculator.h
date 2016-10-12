#ifndef XORFITNESSCALULATOR_H
#define XORFITNESSCALULATOR_H

#include "../../src/FitnessCalculator.h"
#include "../../src/Agent.h"

class XorFitnessCalculator: public FitnessCalculator {
  public:
    XorFitnessCalculator(){}
    ~XorFitnessCalculator(){}
    double calculate(Agent * agent);
};

#endif
