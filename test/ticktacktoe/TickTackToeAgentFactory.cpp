#include "TickTackToeAgentFactory.h"
#include "TickTackToeAgent.h"

TickTackToeAgentFactory::TickTackToeAgentFactory() {

}

TickTackToeAgentFactory::~TickTackToeAgentFactory() {

}


Agent * TickTackToeAgentFactory::newInstance(Genome * genome, NetworkConfiguration * configuration) {
  return new TickTackToeAgent(genome, configuration);
}
