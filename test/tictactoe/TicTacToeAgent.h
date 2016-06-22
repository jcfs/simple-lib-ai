#ifndef TICKTACKTOEAGENT_H
#define TICKTACKTOEAGENT_H

#include <string>

#include "../../src/Agent.h"

using namespace std;

class TicTacToeAgent: public Agent {
  private:
    char game[9];    

  public:
    TicTacToeAgent(Genome * genome, NetworkConfiguration * configuration);
    ~TicTacToeAgent();
    void update();
    bool isAlive();
    bool isDead();
    string toString();
    void die();
    char * getGame(){ return game; }

  private:
    string to_s(char ch);
};


#endif
