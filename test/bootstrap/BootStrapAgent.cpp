#include <iostream>
#include <string>
#include <cstring>

#include "../../src/Util.h"
#include "BootStrapAgent.h"

BootStrapAgent::BootStrapAgent(Genome * genome, NetworkConfiguration * configuration) {
  m_network = new NeuralNetwork(configuration);
  m_genome = genome;
  m_alive = true;
}

// destructor we just need to destruct the neural network
BootStrapAgent::~BootStrapAgent() {
  delete m_network;
}

