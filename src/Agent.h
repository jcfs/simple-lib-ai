#ifndef AGENT_H
#define AGENT_H

#include "NeuralNetwork.h"
#include "NetworkConfiguration.h"
#include "Genome.h"

class Agent {
  protected:
    bool m_alive;
    NeuralNetwork * m_network;
    Genome * m_genome;
  
  public:
    virtual ~Agent(){}
    virtual void update() = 0;
    virtual bool isAlive() = 0;
    virtual bool isDead() = 0;

    Genome * getGenome() { return m_genome; }
};


#endif
