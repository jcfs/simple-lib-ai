#ifndef BOOTSTRAPAGENT_H
#define BOOTSTRAPAGENT_H

#include <string>

#include "../../src/Agent.h"

using namespace std;

class BootStrapAgent: public Agent {
  public:
    BootStrapAgent(Genome * genome, NetworkConfiguration * configuration);
    ~BootStrapAgent();
    void update(){}
    bool isAlive(){ return false; }
    bool isDead(){ return false; }
    string toString(){return NULL;}

};


#endif
