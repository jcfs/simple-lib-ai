#include "MemoryAgentFactory.h"
#include "MemoryAgent.h"

MemoryAgentFactory::MemoryAgentFactory() {

}

MemoryAgentFactory::~MemoryAgentFactory() {

}


Agent * MemoryAgentFactory::newInstance(Genome * genome, NetworkConfiguration * configuration) {
  return new MemoryAgent(genome, configuration);
}
