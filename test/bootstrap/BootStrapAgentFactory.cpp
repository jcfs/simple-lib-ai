#include "BootStrapAgentFactory.h"
#include "BootStrapAgent.h"

BootStrapAgentFactory::BootStrapAgentFactory() {

}

BootStrapAgentFactory::~BootStrapAgentFactory() {

}


Agent * BootStrapAgentFactory::newInstance(Genome * genome, NetworkConfiguration * configuration) {
  return new BootStrapAgent(genome, configuration);
}
