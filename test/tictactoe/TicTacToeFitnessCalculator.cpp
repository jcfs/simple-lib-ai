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
  } else if (result == CIRCLE) {
    agent->getGenome()->setFitness(agent->getGenome()->getFitness() - 15);
  } else if (result == -CROSS) {
    agent->getGenome()->setFitness(10 + agent->getGenome()->getFitness());
  } else {
    agent->getGenome()->setFitness(15 + agent->getGenome()->getFitness());
  }
}

