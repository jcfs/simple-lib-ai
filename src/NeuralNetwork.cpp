/*
    Copyright (c) 2016, 2017, 2018 Joao Salavisa <joao.salavisa@gmail.com>.

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
#include <list>
#include <string>
#include <cmath>
#include "NeuralNetwork.h"
#include "Sigmoid.h"
#include "Util.h"

NeuralNetwork::NeuralNetwork(int inputs, int outputs, int hidden_layers, int neuron_hidden) {
  n_inputs = inputs;
  n_outputs = outputs;
  n_hidden_layers = hidden_layers;
  n_neuron_hidden = neuron_hidden;
}

NeuralNetwork::NeuralNetwork(NetworkConfiguration * configuration) {
  n_inputs = configuration->getInputs();
  n_outputs = configuration->getOutputs();
  n_hidden_layers = configuration->getHiddenLayers();
  n_neuron_hidden = configuration->getNeuronHidden();
}

NeuralNetwork::~NeuralNetwork() {
  // destruct all the neuron in the hidden layers
  for(list<list<Neuron *> >::const_iterator it_s = m_hidden.begin(); it_s != m_hidden.end(); it_s++) {
    list<Neuron *>::const_iterator it_in;

    for(it_in = (*it_s).begin(); it_in != (*it_s).end(); it_in++) {
      delete *it_in;
    }
  }

  // destruct all the neuron in the output layer
  for(list<Neuron *>::const_iterator it = m_output.begin(); it != m_output.end(); it++) {
    delete *it;
  }  
}

void NeuralNetwork::init() {
  // initialize the hidden layers - the first layer is initialized with
  // as many inputs as the number of inputs to the network
  // the subsequent layers will be initialized with as many inputs as neurons
  // per hidden layer
  for(int i = 0; i < this->n_hidden_layers; i++) {
    list<Neuron *> neurons;
    for(int j = 0; j < this->n_neuron_hidden; j++) {
      neurons.push_back(new Neuron(i == 0 ? this->n_inputs + 1 : this->n_neuron_hidden + 1, true));
    }

    this->m_hidden.push_back(neurons);
  }

  // Initialize the output layer with as many inputs as the number of neurons
  // per hidden layer
  for(int i = 0; i < this->n_outputs; i++) {
    this->m_output.push_back(new Neuron(n_neuron_hidden + 1, true));
  }
}

// main update method to the neural network. The input parameter is an array of
// input values, and returns an array of output values
vector<float> NeuralNetwork::feedForward(vector<float> inputs) {
  return evaluateOutputLayer(evaluateHiddenLayers(inputs));
}

// backward pass to update the network weights based on the current error
// we first calculate the total error
double NeuralNetwork::backwardPass(vector<float> output) {
  size_t index = 0;
  double totalError = 0;
  // calculate the error of the output layer based on the desired output
  for(auto &n : m_output) {
    n->setError(0.5 * pow((output[index] - n->getOutput()), 2));
    totalError += n->getError();
    index += 1;
  }

  // update the output layer weights - for that we start on the last hidden layer
  list<list<Neuron *> >::reverse_iterator itr = m_hidden.rbegin();

  size_t currentWeight = 0;

  for(list<Neuron *>::const_iterator ht = (*itr).begin(); ht != (*itr).end(); ht++, currentWeight++) {
    Neuron * n = (*ht);
    size_t c = 0;
    for(auto &ot : m_output) {
      // calculate sigma value for the output neuron
      double s = -(output[c] - ot->getOutput())*ot->getOutput()*(1 - ot->getOutput());
      // TODO: replace the 0.5 literal for a learning rate configurable
      ot->m_prev_weights_delta[currentWeight] = ot->m_weights[currentWeight] - (0.5 * s * n->getOutput());
      //DEBUG("\tNeuron weight error: " << output[currentWeight] << " " << ot->m_prev_weights_delta[currentWeight] << endl);
      c += 1;
    }
  }

  // update neuron weights
  for(auto &n : m_output) {
    for(size_t i = 0; i < n->getWeights().size(); i++) {
      n->m_weights[i] = n->m_prev_weights_delta[i];
    }
  }

  return totalError;
}

// main function to train the network given an input and output vectors
// it uses backpropagation algorithm to update the network weights
// it returns the current error
double NeuralNetwork::train(vector<float> input, vector<float> output) {
  feedForward(input);
  return backwardPass(output);
}

// auxiliary method to import an array of weights to the network neurons
// it is used to recover the state of a previously trained network
void NeuralNetwork::loadWeights(vector<float> weights) {
  int weights_index = 0;

  list<list<Neuron *> >::const_iterator it;

  for(it = m_hidden.begin(); it != m_hidden.end(); it++) {
    list<Neuron *>::const_iterator neuron_it;

    for(neuron_it = (*it).begin(); neuron_it != (*it).end(); neuron_it++) {
      vector<float> weightsVector;      
      for(size_t i = 0; i < (*neuron_it)->getWeights().size(); i++) {
        weightsVector.push_back(weights[weights_index++]);
      }
      (*neuron_it)->setWeights(weightsVector);
    }
  }

  list<Neuron *>::const_iterator output_it;

  for(output_it = m_output.begin(); output_it != m_output.end(); output_it++) {
    vector<float> weightsVector;

    for(size_t i = 0; i < (*output_it)->getWeights().size(); i++) {
      weightsVector.push_back(weights[weights_index++]);
    }

    (*output_it)->setWeights(weightsVector);
  }
}

string NeuralNetwork::toString() {
  string str = "NeuralNetwork:\n";

  str.append("\tinputs: " + to_string(n_inputs) + "\n");
  str.append("\thidden layers: " + to_string(m_hidden.size()) + "\n");
  str.append("\toutputs: " + to_string(m_output.size()) + "\n");

  list<list<Neuron *> >::const_iterator it;
  str.append("\thidden layers weights:\n");
  size_t o = 1;

  for(it = m_hidden.begin(); it != m_hidden.end(); it++) {
    list<Neuron *>::const_iterator neuron_it;

    for(neuron_it = (*it).begin(); neuron_it != (*it).end(); neuron_it++) {
      str.append("\t\th" + to_string(o++) + ": ");     
      for(size_t i = 0; i < (*neuron_it)->getWeights().size(); i++) {
        str.append(to_string((*neuron_it)->getWeights()[i]) + " ");
      }
      str.append("\n");
    }
  }

  list<Neuron *>::const_iterator output_it;
  
  str.append("\toutput weights:\n");
  o = 1;
  for(output_it = m_output.begin(); output_it != m_output.end(); output_it++) {
    str.append("\t\to" + to_string(o++) + ": ");
    for(size_t i = 0; i < (*output_it)->getWeights().size(); i++) {
      str.append(to_string((*output_it)->getWeights()[i]) + " ");
    }
    str.append("\n");
  }
 
  return str;
}

//
// Private methods
//
vector<float> NeuralNetwork::evaluateHiddenLayers(vector<float> inputs) {
  vector<float> hiddenLayerInput = inputs;
  vector<float> hiddenLayerOutput;

  list<list<Neuron *> >::const_iterator it;

  for(it = m_hidden.begin(); it != m_hidden.end(); it++) {
    list<Neuron *>::const_iterator neuron_it;
    for(neuron_it = (*it).begin(); neuron_it != (*it).end(); neuron_it++) {
      Neuron * n = *neuron_it;
      hiddenLayerOutput.push_back(n->evaluate(hiddenLayerInput));
    }

    hiddenLayerInput = hiddenLayerOutput;
  }

  return hiddenLayerOutput;

}

vector<float> NeuralNetwork::evaluateOutputLayer(vector<float> hidden_output) {
  vector<float> outputs;

  list<Neuron *>::const_iterator output_it;

  for(output_it = m_output.begin(); output_it != m_output.end(); output_it++) {
    Neuron * n = *output_it;
    outputs.push_back(n->evaluate(hidden_output));
  }

  return outputs;
}

