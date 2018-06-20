#ifndef TICKTACKTOEAGENT_H
#define TICKTACKTOEAGENT_H

#include <string>

#include "../../src/Agent.h"

using namespace std;

class TicTacToeAgent: public Agent {
  private:
    int won;
    int lost;
    int draw;
    int same;

  public:
    TicTacToeAgent(Genome * genome, NetworkConfiguration * configuration);
    ~TicTacToeAgent();
    void update();
    bool isAlive();
    bool isDead();
    string toString();
    void die();
    int getWon() { return won; };
    int getDraw() { return draw; };
    int getLost() { return lost; };
    int getSame() { return same; };

  private:
    void expandTree(char * currentGame);
    string to_s(char ch);
};


#endif
