#ifndef SINFITNESSCALULATOR_H
#define SINFITNESSCALULATOR_H

#include "../../src/FitnessCalculator.h"
#include "../../src/Agent.h"

class SinFitnessCalculator: public FitnessCalculator {
  public:
    SinFitnessCalculator(){}
    ~SinFitnessCalculator(){}
    double calculate(Agent * agent);
};

#endif
