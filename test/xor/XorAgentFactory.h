#ifndef XORAGENTFACTORY_H
#define XORAGENTFACTORY_H

#include "../../src/Agent.h"
#include "../../src/AgentFactory.h"
#include "../../src/Genome.h"
#include "../../src/NetworkConfiguration.h"

class XorAgentFactory: public AgentFactory {
  public:
    XorAgentFactory();
    ~XorAgentFactory();
    Agent * newInstance(Genome * genome, NetworkConfiguration * configuration);
};

#endif
