#include <iostream>

#include "TicTacToeFitnessCalculator.h"
#include "TicTacToeAgent.h"
#include "TicTacToeValidator.h"

double TicTacToeFitnessCalculator::calculate(Agent * agent) {
  TicTacToeAgent * tAgent = (TicTacToeAgent *) agent;
  int total = tAgent->getDraw() + tAgent->getWon() + tAgent->getLost();
  return tAgent->getSame();
}

