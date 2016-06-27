#ifndef MEMORYAGENT_H
#define MEMORYAGENT_H

#include <string>

#include "../../src/Agent.h"

using namespace std;

class MemoryAgent: public Agent {
  public:
    MemoryAgent(Genome * genome, NetworkConfiguration * configuration);
    ~MemoryAgent();
    void update(){}
    bool isAlive(){ return false; }
    bool isDead(){ return false; }
    string toString(){return NULL;}

};


#endif
