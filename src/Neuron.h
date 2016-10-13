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

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cmath>

#define ERR_INVAL -1

using namespace std;

class Neuron {
  public:
    /* constructors */
    Neuron(int inputs, bool sigmoid);
    Neuron(Neuron * neuron);

    virtual ~Neuron();

    float evaluate(vector<float> inputs);

    /* getters/setters */
    void setInputs(vector<float> inputs) { m_inputs = inputs; }
    vector<float> getInputs() { return m_inputs; }

    void setWeights(vector<float> weights);
    vector<float> getWeights() { return m_weights; }

    void setPrevWeightsDelta(vector<float> weights) { m_prev_weights_delta = weights; }
    vector<float> getPrevWeightsDelta() { return m_prev_weights_delta; }

    void setSigmoid(bool sigmoid) { m_sigmoid = sigmoid; }
    bool getSigmoid() { return m_sigmoid; }

    void setError(double error) { m_error = error; }
    double getError() { return m_error; }

    void setOutput(double output) { m_output = output; }
    double getOutput() { return m_output; };

  private:
    vector<float> m_inputs;
    vector<float> m_weights;
    vector<float> m_prev_weights_delta;

    bool m_sigmoid;
    double m_error;
    double m_output;
};

#endif
