#ifndef TICKTACKTOEFITNESSCALULATOR_H
#define TICKTACKTOEFITNESSCALULATOR_H

#include "../../src/FitnessCalculator.h"
#include "../../src/Agent.h"
#include "TicTacToeAgent.h"

class TicTacToeFitnessCalculator: public FitnessCalculator {
  public:
    TicTacToeFitnessCalculator(){}
    ~TicTacToeFitnessCalculator(){}
    void calculate(Agent * agent);

  private:
    bool validateDiagonals(char ** game, char sym);
    bool validateHorizontals(char ** game, char sym);
    bool validateVerticals(char ** game, char sym);
};

#endif
