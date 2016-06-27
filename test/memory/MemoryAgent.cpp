#include <iostream>
#include <string>
#include <cstring>

#include "../../src/Util.h"
#include "MemoryAgent.h"

MemoryAgent::MemoryAgent(Genome * genome, NetworkConfiguration * configuration) {
  m_network = new NeuralNetwork(configuration);
  m_genome = genome;
  m_alive = true;
}

// destructor we just need to destruct the neural network
MemoryAgent::~MemoryAgent() {
  delete m_network;
}

