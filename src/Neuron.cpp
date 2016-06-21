#include <iostream>

#include "RandomUtil.h"
#include "Neuron.h"

using namespace std;

Neuron::Neuron(int n) {
  m_sigmoid = true;
  
  for(int i = 0; i < n; i++) {
    m_weights.push_back(RandomUtil::nextClampedFloat());
  }
}

Neuron::Neuron(Neuron * neuron) {
  m_sigmoid = neuron->getSigmoid();
  m_weights.reserve(neuron->getWeights().size());

  for(size_t i = 0; i < neuron->getWeights().size(); i++) {
    m_weights.push_back(neuron->getWeights()[i]);
  } 
}

float Neuron::evaluate(vector<float> inputs) {
  float net = 0;

  if (inputs.size() != m_weights.size()-1) {
    return ERR_INVAL;
  }

  for(size_t i = 0; i < inputs.size(); i++) {
    net += inputs[i] * m_weights[i];
  }

  net += m_weights[m_weights.size() - 1] * -1.0; // bias

  return m_sigmoid ? sigmoid(net) : net;
}

void Neuron::setWeights(vector<float> weights) {
  m_weights = weights;
}
