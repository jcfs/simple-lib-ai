#ifndef AGENT_H
#define AGENT_H

#include "NeuralNetwork.h"
#include "NetworkConfiguration.h"
#include "Genome.h"

class Agent {
  private:
    bool m_alive;
    NeuralNetwork * network;
    Genome * genome;
  
  public:
    Agent(Genome * genome, NetworkConfiguration * configuration);
    ~Agent();

    virtual void update();
    bool isAlive() { return m_alive; }
    bool isDead() { return !m_alive; }
};


#endif
