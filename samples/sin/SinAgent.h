#ifndef SINAGENT_H
#define SINAGENT_H

#include <string>

#include "../../src/Agent.h"

using namespace std;

class SinAgent: public Agent {
  private:
    float m_error;

  public:
    SinAgent(Genome * genome, NetworkConfiguration * configuration);
    ~SinAgent();
    void update();
    bool isAlive(){ return m_alive; }
    bool isDead(){ return m_alive; }
    string toString();
    float getError() { return m_error; }

};


#endif
