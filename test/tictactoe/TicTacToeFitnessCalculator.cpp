#include <iostream>

#include "TicTacToeFitnessCalculator.h"
#include "TicTacToeAgent.h"
#include "TicTacToeValidator.h"

double TicTacToeFitnessCalculator::calculate(Agent * agent) {
  TicTacToeAgent * tAgent = (TicTacToeAgent *) agent;
  double total = tAgent->getDraw() + tAgent->getWon() + tAgent->getLost();
  // percentage of not lost
  return ((total - (tAgent->getLost())) / total) * 100.0;
}

