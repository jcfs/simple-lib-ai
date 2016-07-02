#ifndef BOOTSTRAPAGENTFACTORY_H
#define BOOTSTRAPAGENTFACTORY_H

#include "../../src/Agent.h"
#include "../../src/AgentFactory.h"
#include "../../src/Genome.h"
#include "../../src/NetworkConfiguration.h"

class BootStrapAgentFactory: public AgentFactory {
  public:
    BootStrapAgentFactory();
    ~BootStrapAgentFactory();
    Agent * newInstance(Genome * genome, NetworkConfiguration * configuration);
};

#endif
