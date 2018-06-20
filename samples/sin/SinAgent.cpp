#include <iostream>
#include <string>
#include <cstring>

#include "../../src/Util.h"
#include "SinAgent.h"

SinAgent::SinAgent(Genome * genome, NetworkConfiguration * configuration) {
  m_network = new NeuralNetwork(configuration);
  m_genome = genome;
  m_alive = true;
}

// destructor we just need to destruct the neural network
SinAgent::~SinAgent() {
  delete m_network;
}

void SinAgent::update() {
  m_error = 0;

  for(float i = 0; i <= 3.14; i += 0.01) {

    vector<float> input;
    input.push_back(i);
    vector<float> output = m_network->feedForward(input);

    float c_sin = output[0];
    float r_sin = sin(i);

    m_error += abs(r_sin - c_sin);
  }

  m_alive = false;
}

string SinAgent::toString() {
  string str = "SinAgent: ";

  str.append("status=" + (m_alive ? to_string(1) : to_string(0)));
  str.append(" Genome: [");

  double checkSum = 0;
  for(size_t i = 0; i < 4; i++) {
    str.append(std::to_string(m_genome->getGenes()[i]));
    checkSum += m_genome->getGenes()[i];
    if (i+1 != m_genome->getGenes().size()) {
      str.append(", ");
    }
  }
  str.append("...] Error: " + to_string(m_error) + " Fitness: " + to_string(m_genome->getFitness()) + "\n");
  str.append("\n");

  return str;
}
