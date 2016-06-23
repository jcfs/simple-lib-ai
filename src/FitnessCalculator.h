#ifndef FITNESSCALCULATOR_H
#define FITNESSCALCULATOR_H

#include "Agent.h"

class FitnessCalculator {
  public:
    FitnessCalculator(){}
    virtual ~FitnessCalculator(){}
    virtual double calculate(Agent * agent) = 0;
};

#endif
