#ifndef SINAGENTFACTORY_H
#define SINAGENTFACTORY_H

#include "../../src/Agent.h"
#include "../../src/AgentFactory.h"
#include "../../src/Genome.h"
#include "../../src/NetworkConfiguration.h"

class SinAgentFactory: public AgentFactory {
  public:
    SinAgentFactory();
    ~SinAgentFactory();
    Agent * newInstance(Genome * genome, NetworkConfiguration * configuration);
};

#endif
