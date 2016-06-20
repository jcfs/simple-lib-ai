#ifndef TICKTACKTOWAGENTFACTORY_H
#define TICKTACKTOWAGENTFACTORY_H

#include "../../src/Agent.h"
#include "../../src/AgentFactory.h"
#include "../../src/Genome.h"
#include "../../src/NetworkConfiguration.h"

class TickTackToeAgentFactory: public AgentFactory {
  public:
    TickTackToeAgentFactory();
    ~TickTackToeAgentFactory();
    Agent * newInstance(Genome * genome, NetworkConfiguration * configuration);
};

#endif
