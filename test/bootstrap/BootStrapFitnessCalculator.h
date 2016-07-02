#ifndef BOOTSTRAPFITNESSCALULATOR_H
#define BOOTSTRAPFITNESSCALULATOR_H

#include "../../src/FitnessCalculator.h"
#include "../../src/Agent.h"

class BootStrapFitnessCalculator: public FitnessCalculator {
  public:
    BootStrapFitnessCalculator(){}
    ~BootStrapFitnessCalculator(){}
    double calculate(Agent * agent);
};

#endif
