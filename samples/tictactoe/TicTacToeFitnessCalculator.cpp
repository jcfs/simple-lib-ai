#include <iostream>

#include "TicTacToeFitnessCalculator.h"
#include "TicTacToeAgent.h"
#include "TicTacToeValidator.h"

double TicTacToeFitnessCalculator::calculate(Agent * agent) {
  TicTacToeAgent * tAgent = (TicTacToeAgent *) agent;
  double total = tAgent->getDraw() + tAgent->getWon() + tAgent->getLost();
  // percentage of not lost
  return (tAgent->getDraw()*0.1f + tAgent->getWon()) - tAgent->getLost()*2;
}

