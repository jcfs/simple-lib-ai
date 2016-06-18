#ifndef NETWORK_CONFIGURATION_H
#define NETWORK_CONFIGURATION_H

class NetworkConfiguration {

  private:
    int m_inputs;
    int m_hidden_layers;
    int m_neuron_hidden;
    int m_outputs;

  public:
    // constructor
    NetworkConfiguration(int inputs, int hidden_layers, int neuron_hidden, int outputs);
   
    int getInputs() { return m_inputs; }
    int getHiddenLayers() { return m_hidden_layers; }
    int getNeuronHidden() { return m_neuron_hidden; }
    int getOutputs() { return m_outputs; }

};


#endif
