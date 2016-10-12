#include "XorAgentFactory.h"
#include "XorAgent.h"

XorAgentFactory::XorAgentFactory() {

}

XorAgentFactory::~XorAgentFactory() {

}


Agent * XorAgentFactory::newInstance(Genome * genome, NetworkConfiguration * configuration) {
  return new XorAgent(genome, configuration);
}
