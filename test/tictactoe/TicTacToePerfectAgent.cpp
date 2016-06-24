#include <iostream>

#include "TicTacToePerfectAgent.h"
#include "TicTacToeValidator.h"

int TicTacToePerfectAgent::play(char * game, int player) {

  int move = -1;
  int score = -2;

  int c = 0;

  for(int i = 0; i < 9; i++) {
    if (game[i] != BLANK)
      c++;
  }

  if (c == 0) {
    return 4;
  }

  for(int i = 0; i < 9; ++i) {
    if(game[i] == 0) {
      game[i] = 1;
      int tempScore = -minmax(game, -1);
      game[i] = 0;
      if(tempScore > score) {
        score = tempScore;
        move = i;
      }
    }
  }

  return move;
}

int TicTacToePerfectAgent::minmax(char * game, int player) {
    //How is the position like for player (their turn) on game?
    int winner = TicTacToeValidator::validate(game);
    if(winner != 0 && winner != -3) return winner*player;

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(game[i] == 0) {//If legal,
            game[i] = player;//Try the move
            int thisScore = -minmax(game, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            game[i] = 0;//Reset game after try
        }
    }
    if(move == -1) return 0;
    return score;
}
