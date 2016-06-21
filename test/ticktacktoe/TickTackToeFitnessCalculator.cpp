#include <iostream>

#include "TickTackToeFitnessCalculator.h"
#include "TickTackToeAgent.h"

void TickTackToeFitnessCalculator::calculate(Agent * agent) {
  TickTackToeAgent * tAgent = (TickTackToeAgent *) agent;

  char * game = tAgent->getGame();

  int board[8][3] = {{0,1,2},
    {3,4,5},
    {6,7,8},
    {0,3,6},
    {1,4,7},
    {2,5,8},
    {0,4,8},
    {2,4,6}};


  bool pcWin = false;
  bool aiWin = false;

  for(int i = 0; i < 8; i++) {
    if (game[board[i][0]] == game[board[i][1]] && game[board[i][0]] == game[board[i][2]] && game[board[i][0]] != BLANK) {
      if (game[board[i][0]] == CIRCLE) {
        pcWin = true;
      } else {
        aiWin = true;
      }
    }
  }

  bool draw = true;
  int count = 0;
  for(int i = 0; i < 9; i++) {
    if (game[i] == BLANK) {
      count++;
    }
  }

  draw = (count == 0) && !pcWin && !aiWin;

  if (agent->getGenome()->getFitness() < 0) {
  } else {
    if (pcWin) {
      agent->getGenome()->setFitness(-1);
    } else if (aiWin) {
      agent->getGenome()->setFitness(100-count);
    } else {
      agent->getGenome()->setFitness(100-count-10);
    }
  }

}

