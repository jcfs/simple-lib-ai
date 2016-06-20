#ifndef TICKTACKTOEAGENT_H
#define TICKTACKTOEAGENT_H

#include <string>

#include "../../src/Agent.h"

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
