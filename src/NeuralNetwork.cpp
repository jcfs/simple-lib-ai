#include <list>
#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(NetworkConfiguration configuration) {
  int inputs = configuration.getInputs();
  int outputs = configuration.getOutputs();
  int hidden = configuration.getHiddenLayers();
  int neuron_hidden = configuration.getNeuronHidden();
  
  // initialize the hidden layers - the first layer is initialized with
  // as many inputs ad the number of inputs to the network
  // the subsequent layers will be initialized with as many inputs as neurons
  // per hidden layer
  for(int i = 0; i < hidden; i++) {
    list<Neuron *> neurons;
    for(int j = 0; j < neuron_hidden; j++) {
      neurons.push_back(new Neuron(i == 0 ? inputs + 1 : neuron_hidden + 1));
    }

    m_hidden.push_back(neurons);
  }

  // Initialize the output layer with as many inputs as the number of neurons
  // per hidden layer
  for(int i = 0; i < outputs; i++) {
    m_output.push_back(new Neuron(neuron_hidden + 1));
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
vector<float> NeuralNetwork::update(vector<float> inputs) {
  return NeuralNetwork::evaluateOutputLayer(NeuralNetwork::evaluateHiddenLayers(inputs));
}

// auxiliary method to import an array of weights to the network neurons
// it is used to recover the state of a previously trained network
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

// auxiliary method to export and array of weights of the network
// neurons. It can be used to be imported later to recover the
// state of the network
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

