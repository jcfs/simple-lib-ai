#ifndef TICKTACKTOEFITNESSCALULATOR_H
#define TICKTACKTOEFITNESSCALULATOR_H

#include "../../src/FitnessCalculator.h"
#include "../../src/Agent.h"
#include "TickTackToeAgent.h"

class TickTackToeFitnessCalculator: public FitnessCalculator {
  public:
    TickTackToeFitnessCalculator(){}
    ~TickTackToeFitnessCalculator(){}
    void calculate(Agent * agent);

  private:
    bool validateDiagonals(char ** game, char sym);
    bool validateHorizontals(char ** game, char sym);
    bool validateVerticals(char ** game, char sym);
};

#endif
