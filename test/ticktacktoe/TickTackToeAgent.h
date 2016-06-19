#ifndef TICKTACKTOEAGENT_H
#define TICKTACKTOEAGENT_H

#include <string>

#include "../../src/Agent.h"

using namespace std;

class TickTackToeAgent: public Agent {

  public:
    TickTackToeAgent(Genome * genome, NetworkConfiguration * configuration);
    ~TickTackToeAgent();
    void update();
    bool isAlive();
    bool isDead();
    string toString();

};


#endif
