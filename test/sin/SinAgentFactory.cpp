#include "SinAgentFactory.h"
#include "SinAgent.h"

SinAgentFactory::SinAgentFactory() {

}

SinAgentFactory::~SinAgentFactory() {

}


Agent * SinAgentFactory::newInstance(Genome * genome, NetworkConfiguration * configuration) {
  return new SinAgent(genome, configuration);
}
