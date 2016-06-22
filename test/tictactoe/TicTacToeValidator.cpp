#include <iostream>

#include "TicTacToeValidator.h"

int TicTacToeValidator::validate(char * game) {
  int board[8][3] = {{0,1,2},
    {3,4,5},
    {6,7,8},
    {0,3,6},
    {1,4,7},
    {2,5,8},
    {0,4,8},
    {2,4,6}};


  bool circleWin = false;
  bool crossWin = false;

  for(int i = 0; i < 8; i++) {
    if (game[board[i][0]] == game[board[i][1]] && game[board[i][0]] == game[board[i][2]] && game[board[i][0]] != BLANK) {
      if (game[board[i][0]] == CIRCLE) {
        circleWin = true;
      } else {
        crossWin = true;
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

  draw = (count == 0) && !circleWin && !crossWin;

  if (circleWin) {
    return CIRCLE;
  } else if (crossWin) {
    return CROSS;
  } else if (draw) {
    return BLANK;
  } else {
    return NOT_OVER;
  }
}

