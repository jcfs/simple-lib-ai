#ifndef TICKTACKTOWAGENTFACTORY_H
#define TICKTACKTOWAGENTFACTORY_H

#include "../../src/Agent.h"
#include "../../src/AgentFactory.h"
#include "../../src/Genome.h"
#include "../../src/NetworkConfiguration.h"

class TicTacToeAgentFactory: public AgentFactory {
  public:
    TicTacToeAgentFactory();
    ~TicTacToeAgentFactory();
    Agent * newInstance(Genome * genome, NetworkConfiguration * configuration);
};

#endif
