#ifndef TICKTACKTOEAGENT_H
#define TICKTACKTOEAGENT_H

#include <string>

#include "../../src/Agent.h"

#define CIRCLE 1
#define CROSS  2
#define BLANK  0

using namespace std;

class TickTackToeAgent: public Agent {
  private:
    char game[9];    

  public:
    TickTackToeAgent(Genome * genome, NetworkConfiguration * configuration);
    ~TickTackToeAgent();
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
