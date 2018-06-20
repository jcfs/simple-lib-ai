#ifndef TICTACTOEPERFECTAGENT_H
#define TICTACTOEPERFECTAGENT_H

#include "TicTacToeValidator.h"

class TicTacToePerfectAgent {

  public:
    static int play(char * game, int player);

  private:
    static int minmax(char * game, int player);
};


#endif
