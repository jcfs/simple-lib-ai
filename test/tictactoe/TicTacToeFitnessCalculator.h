#ifndef TICKTACKTOEFITNESSCALULATOR_H
#define TICKTACKTOEFITNESSCALULATOR_H

#include "../../src/FitnessCalculator.h"
#include "../../src/Agent.h"
#include "TicTacToeAgent.h"

class TicTacToeFitnessCalculator: public FitnessCalculator {
  public:
    TicTacToeFitnessCalculator(){}
    ~TicTacToeFitnessCalculator(){}
    double calculate(Agent * agent);
};

#endif
