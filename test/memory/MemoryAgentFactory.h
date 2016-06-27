#ifndef MEMORYAGENTFACTORY_H
#define MEMORYAGENTFACTORY_H

#include "../../src/Agent.h"
#include "../../src/AgentFactory.h"
#include "../../src/Genome.h"
#include "../../src/NetworkConfiguration.h"

class MemoryAgentFactory: public AgentFactory {
  public:
    MemoryAgentFactory();
    ~MemoryAgentFactory();
    Agent * newInstance(Genome * genome, NetworkConfiguration * configuration);
};

#endif
