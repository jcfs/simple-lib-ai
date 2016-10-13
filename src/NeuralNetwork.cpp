/*
    Copyright (c) 2016 Joao Salavisa <joao.salavisa@gmail.com>.

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
#include "NeuralNetwork.h"
#include "Sigmoid.h"

NeuralNetwork::NeuralNetwork(NetworkConfiguration * configuration) {
  int inputs = configuration->getInputs();
  int outputs = configuration->getOutputs();
  int hidden = configuration->getHiddenLayers();
  int neuron_hidden = configuration->getNeuronHidden();

  // initialize the hidden layers - the first layer is initialized with
  // as many inputs ad the number of inputs to the network
  // the subsequent layers will be initialized with as many inputs as neurons
  // per hidden layer
  for(int i = 0; i < hidden; i++) {
    list<Neuron *> neurons;
    for(int j = 0; j < neuron_hidden; j++) {
      neurons.push_back(new Neuron(i == 0 ? inputs + 1 : neuron_hidden + 1, true));
    }

    m_hidden.push_back(neurons);
  }

  // Initialize the output layer with as many inputs as the number of neurons
  // per hidden layer
  for(int i = 0; i < outputs; i++) {
    m_output.push_back(new Neuron(neuron_hidden + 1, false));
  }
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


// main update method to the neural network. The input parameter is an array of
// input values, and returns an array of output values
vector<float> NeuralNetwork::feedForward(vector<float> inputs) {
  return evaluateOutputLayer(evaluateHiddenLayers(inputs));
}

// main function to train the network given an input and output vectors
// it uses backpropagation algorithm to update the network weights
// it returns the current error
float NeuralNetwork::train(vector<float> input, vector<float> output) {
  size_t index = 0;
  // feed forward the input to get an output
  feedForward(input);

  // calculate the error of the output layer based on the desired output
  for(list<Neuron *>::const_iterator it = m_output.begin(); it != m_output.end(); it++, index++) {
    Neuron * n = *it;
    n->setError((output[index] - n->getOutput()) * Sigmoid::dSigmoid(n->getOutput()));
  }

  list<list<Neuron *> >::const_iterator it;

  //calculate the errors for all the hidden layers
  for(it = m_hidden.end(); it != m_hidden.begin(); it--) {
    // if this is the last layer before output layer
    list<Neuron *> h_layer = *it;

    for(list<Neuron *>::const_iterator ht = h_layer.begin(); ht != h_layer.end(); ht++) {
      Neuron * n = *ht;
      double delta_sum = 0;

      if (it == m_hidden.end()) {
        // if it is the last layer we need to use the weights of the output to calculate the error
        for(list<Neuron *>::const_iterator ot = m_output.begin(); ot != m_output.end(); ot++) {
          Neuron * on = *ot;
          for(size_t i = 0; i < on->getWeights().size(); i++) {
            delta_sum += on->getError() * on->getWeights()[i]; 
          }
        }
      } else {
        // if it is not the last layer we need to iterate over the neurons of the next layer
        ++it;
        list<Neuron *> next_layer = *(it);

        for(list<Neuron *>::const_iterator nl = next_layer.begin(); nl != next_layer.end(); nl++) {
          Neuron * nno = *nl;
          for(size_t i = 0; i < nno->getWeights().size(); i++) {
            delta_sum += nno->getError() * nno->getWeights()[i];
          }
        }
        --it;
      }

      n->setError(Sigmoid::dSigmoid(n->getOutput()) * delta_sum);
    }
  }

  //update the weights accordingly
  for(it = m_hidden.begin(); it != m_hidden.end(); it++) {
    list<Neuron *> layer = *it;

    for(list<Neuron *>::const_iterator ht = layer.begin(); ht != layer.end(); ht++) {
      Neuron * n = *ht;

      for(size_t i = 0; i < n->getWeights().size() - 1; i++) {
        n->getWeights()[i] += 0.2 * n->getPrevWeightsDelta()[i];
        n->getPrevWeightsDelta()[i] = 0.2 * n->getError() * n->getInputs()[i];
        n->getWeights()[i] += n->getPrevWeightsDelta()[i];
      }

      //adjust the bias
      size_t b = n->getWeights().size() - 1;
      n->getWeights()[b] += 0.2 * n->getPrevWeightsDelta()[b];
      n->getPrevWeightsDelta()[b] = 0.2 * n->getError(); 
      n->getWeights()[b] += n->getPrevWeightsDelta()[b];
    }
  }

  double error = 0.0;
  // return the error
  index = 0;
  for(list<Neuron *>::const_iterator it = m_output.begin(); it != m_output.end(); it++, index++) {
    error += 0.5 * pow(output[index] - (*it)->getOutput(), 2);
  }

  return error;
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

