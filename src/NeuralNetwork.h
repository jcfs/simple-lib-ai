#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <list>

#include "Neuron.h"
#include "NetworkConfiguration.h"

using namespace std;

class NeuralNetwork {
  private:
    list<list<Neuron *> > m_hidden;
    list<Neuron *> m_output; 
  
  public:
    /* contstuctor */
    NeuralNetwork(NetworkConfiguration * configuration);
    ~NeuralNetwork();
    
    /* main update method */
    vector<float> update(vector<float> input);
    
    /* import and export information to later reuse */
    void importWeights(vector<float> weights);
    vector<float> exportWeights();
    int getWeightCount();
    
  private:
    vector<float> evaluateHiddenLayers(vector<float> inputs);
    vector<float> evaluateOutputLayer(vector<float> hidden_output);
};

#endif
