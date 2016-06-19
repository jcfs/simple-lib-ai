#include <iostream>
#include <string>

#include "TickTackToeAgent.h"

TickTackToeAgent::TickTackToeAgent(Genome * genome, NetworkConfiguration * configuration) {
  m_network = new NeuralNetwork(configuration);
  m_genome = genome;
  m_alive = true;
}

TickTackToeAgent::~TickTackToeAgent() {
  delete m_network;
}

void TickTackToeAgent::update() {
  m_genome->mutate();
}

bool TickTackToeAgent::isAlive() {
  return m_alive;
}

bool TickTackToeAgent::isDead() {
  return !m_alive;
}

string TickTackToeAgent::toString() {
  string str = "TickTackToeAgent: ";
  
  str.append("status=" + (m_alive ? to_string(1) : to_string(0)));
  str.append(" Genome: [");
  for(size_t i = 0; i < m_genome->getGenes().size(); i++) {
    str.append(std::to_string(m_genome->getGenes()[i]));
    if (i+1 != m_genome->getGenes().size()) {
      str.append(", ");
    }
  }
  str.append("]\n");

  return str;
}
