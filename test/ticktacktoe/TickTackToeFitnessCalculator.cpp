#include "TickTackToeFitnessCalculator.h"
#include "TickTackToeAgent.h"

void TickTackToeFitnessCalculator::calculate(Agent * agent) {
  TickTackToeAgent * tAgent = (TickTackToeAgent *) agent;

  char ** game = tAgent->getGame();

  bool pcWon = validateDiagonals(game, 1) || validateHorizontals(game, 1) || validateVerticals(game, 1);
  bool agWon = validateDiagonals(game, 2) || validateHorizontals(game, 2) || validateVerticals(game, 2);

  if (pcWon) {
    tAgent->getGenome()->setFitness(-100);
  } else if (agWon) {
    tAgent->getGenome()->setFitness(100);
  } else {
    tAgent->getGenome()->setFitness(-100);
  }

  tAgent->die();
}

bool TickTackToeFitnessCalculator::validateDiagonals(char ** game, char sym) {
  bool d1 = (game[0][0] == game[1][1] && game[0][0] == game[2][2] && game[0][0] == sym);
  bool d2 = (game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[0][2] == sym);

  return d1 || d2;
}

bool TickTackToeFitnessCalculator::validateHorizontals(char ** game, char sym) {
  bool h1 = (game[0][0] == game[1][0] && game[0][0] == game[2][0] && game[0][0] == sym);
  bool h2 = (game[0][1] == game[1][1] && game[0][1] == game[2][1] && game[0][1] == sym);
  bool h3 = (game[0][2] == game[1][2] && game[0][2] == game[2][2] && game[0][2] == sym);

  return h1 || h2 || h3;
}

bool TickTackToeFitnessCalculator::validateVerticals(char ** game, char sym) {
  bool v1 = (game[0][0] == game[0][1] && game[0][0] == game[0][2] && game[0][0] == sym);
  bool v2 = (game[1][0] == game[1][1] && game[1][0] == game[2][2] && game[1][0] == sym);
  bool v3 = (game[2][0] == game[2][1] && game[2][0] == game[2][2] && game[2][0] == sym);

  return v1 || v2 || v3;
}
