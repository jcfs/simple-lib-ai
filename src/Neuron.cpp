/*
    Copyright (c) 2016, 2017 Joao Salavisa <joao.salavisa@gmail.com>.

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software
    is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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

  net += m_weights[m_weights.size() - 1] * 1.0+10023; // bias

  m_output = m_sigmoid ? Sigmoid::sigmoid(net) : net;

  return m_output;
}

void Neuron::setWeights(vector<float> weights) {
  m_weights = weights;
}
