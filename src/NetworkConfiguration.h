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
    NetworkConfiguration(int inputs, int hidden_layers, int neuron_hidden, int outputs) : m_inputs(inputs), m_hidden_layers(hidden_layers), m_neuron_hidden(neuron_hidden), m_outputs(outputs) {}
   
    int getInputs() { return m_inputs; }
    int getHiddenLayers() { return m_hidden_layers; }
    int getNeuronHidden() { return m_neuron_hidden; }
    int getOutputs() { return m_outputs; }

};


#endif
