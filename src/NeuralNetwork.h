#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <list>

#include "Neuron.h"

using namespace std;

class NeuralNetwork {
  private:
    list<list<Neuron *>> m_hidden;
    list<Neuron *> m_output; 
  
  public:
    /* contstuctor */
    NeuralNetwork(int inputs, int outputs, int hidden, neuron_hidden);
    
    /* main update method */
    list<float> update(list<float> input);
    
    /* import and export information to later reuse */
    void importWeights(vector<float> weights);
    vector<float> exportWeights();
    int getWeightCount();
    
  private:
    list<float> evaluateHiddenLayers(list<float> inputs);
    list<float> evaluateOutputLayer(list<float> hidden_output);
}

#endif
