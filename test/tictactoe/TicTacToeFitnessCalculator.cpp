#include <iostream>

#include "TicTacToeFitnessCalculator.h"
#include "TicTacToeAgent.h"
#include "TicTacToeValidator.h"

void TicTacToeFitnessCalculator::calculate(Agent * agent) {
  TicTacToeAgent * tAgent = (TicTacToeAgent *) agent;

  char * game = tAgent->getGame();

  int result = TicTacToeValidator::validate(game);

  if (result == NOT_OVER) {
    // WTF
  } else if (result == 0) {
    agent->getGenome()->setFitness(-1);
  } else if (result == 1) {
    agent->getGenome()->setFitness(100);
  } else {
    agent->getGenome()->setFitness(99);
  }
}

