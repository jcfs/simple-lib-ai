#ifndef MEMORYFITNESSCALULATOR_H
#define MEMORYFITNESSCALULATOR_H

#include "../../src/FitnessCalculator.h"
#include "../../src/Agent.h"

class MemoryFitnessCalculator: public FitnessCalculator {
  public:
    MemoryFitnessCalculator(){}
    ~MemoryFitnessCalculator(){}
    double calculate(Agent * agent);
};

#endif
