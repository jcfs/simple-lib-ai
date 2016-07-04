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
    vector<float> m_weights;
    vector<float> m_prev_weights_delta;

    bool m_sigmoid;
    double m_error;
    double m_output;
};

#endif
