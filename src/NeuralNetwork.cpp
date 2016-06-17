#include <list>

#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int inputs, int outputs, int hidden, int neuron_hidden) {
  for(int i = 0; i < hidden; i++) {
    list<Neuron *> neurons;
    
    for(int j = 0; j < neuron_hidden; j++) {
      if (i == 0) {
        neurons.push_back(new Neuron(inputs + 1));
      } else {
        neurons.push_back(new Neuron(neuron_hidden + 1));
      }
    }
    
    m_hidden.push_back(neurons);
  }

  // Initialize the outputs with as many inputs as the number of neurons
  // per hidden layer
  for(int i = 0; i < outputs; i++) {
    m_output.push_back(new Neuron(neuron_hidden + 1));
  }
}

vector<float> NeuralNetwork::update(vector<float> inputs) {
    vector<float> hiddenLayerOutput = NeuralNetwork::evaluateHiddenLayers(inputs);
    return NeuralNetwork::evaluateOutputLayer(hiddenLayerOutput);
}

void NeuralNetwork::importWeights(vector<float> weights) {

  int weights_index = 0;

  list<list<Neuron *> >::const_iterator it;

  for(it = m_hidden.begin(); it != m_hidden.end(); it++) {
    list<Neuron *>::const_iterator neuron_it;

    for(neuron_it = (*it).begin(); neuron_it != (*it).end(); neuron_it++) {
      vector<float> weightsVector;      
      for(int i = 0; i < (*neuron_it)->getWeights().size(); i++) {
        weightsVector.push_back(weights[weights_index++]);
      }
      (*neuron_it)->setWeights(weightsVector);
    }
  }

  list<Neuron *>::const_iterator output_it;

  for(output_it = m_output.begin(); output_it != m_output.end(); output_it++) {
    vector<float> weightsVector;

    for(int i = 0; i < (*output_it)->getWeights().size(); i++) {
      weightsVector.push_back(weights[weights_index++]);
    }

    (*output_it)->setWeights(weightsVector);
  }
}

vector<float> NeuralNetwork::exportWeights() {
  vector<float> weights;

  list<list<Neuron *> >::const_iterator it;

  for(it = m_hidden.begin(); it != m_hidden.end(); it++) {
    list<Neuron *>::const_iterator neuron_it;
    for(neuron_it = (*it).begin(); neuron_it != (*it).end(); neuron_it++) {
      for(int i = 0; (*neuron_it)->getWeights().size(); i++) {
        weights.push_back((*neuron_it)->getWeights()[i]);
      }
    }
  }

  list<Neuron *>::const_iterator output_it;

  for(output_it = m_output.begin(); output_it != m_output.end(); output_it++) {
    for(int i = 0; i < (*output_it)->getWeights().size(); i++) {
      weights.push_back((*output_it)->getWeights()[i]);
    }
  }

  return weights;
}

int NeuralNetwork::getWeightCount() {
    return NeuralNetwork::exportWeights().size();
}

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

