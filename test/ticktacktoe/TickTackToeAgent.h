#ifndef TICKTACKTOEAGENT_H
#define TICKTACKTOEAGENT_H

#include <string>

#include "../../src/Agent.h"

#define CIRCLE 1
#define CROSS  2
#define BLANK  3

using namespace std;

class TickTackToeAgent: public Agent {
  private:
    char game[3][3];    

  public:
    TickTackToeAgent(Genome * genome, NetworkConfiguration * configuration);
    ~TickTackToeAgent();
    void update();
    bool isAlive();
    bool isDead();
    string toString();
    void die();
    char ** getGame(){ return (char **) game; }

};


#endif
