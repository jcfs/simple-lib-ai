#include <iostream>

#include "RandomUtil.h"
#include "Neuron.h"
#include "Sigmoid.h"

using namespace std;

Neuron::Neuron(int n, bool sigmoid) {
  m_sigmoid = sigmoid;
  
  for(int i = 0; i < n; i++) {
    m_weights.push_back(RandomUtil::nextClampedFloat());
    m_prev_weights_delta.push_back(0.0);
  }
}

Neuron::Neuron(Neuron * neuron) {
  m_sigmoid = neuron->getSigmoid();
  m_weights.reserve(neuron->getWeights().size());

  for(size_t i = 0; i < neuron->getWeights().size(); i++) {
    m_weights.push_back(neuron->getWeights()[i]);
    m_prev_weights_delta.push_back(0.0);
  } 
}

Neuron::~Neuron() {
  // nothing to destroy
}

float Neuron::evaluate(vector<float> inputs) {
  float net = 0;

  if (inputs.size() != m_weights.size()-1) {
    return ERR_INVAL;
  }

	m_inputs = inputs;

  for(size_t i = 0; i < inputs.size(); i++) {
    net += inputs[i] * m_weights[i];
  }

  net += m_weights[m_weights.size() - 1] * -1.0; // bias

  m_output = m_sigmoid ? Sigmoid::sigmoid(net) : net;

  return m_output;
}

void Neuron::setWeights(vector<float> weights) {
  m_weights = weights;
}
