#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cmath>

#define EINVAL -1

using namespace std;

class Neuron {
  private:
    vector<float> m_weights;
    bool m_sigmoid;

  public:
    /* constructors */
    Neuron(int inputs);
    Neuron(Neuron * neuron);
    float evaluate(vector<float> inputs);
    
    /* getters/setters */
    void setWeights(vector<float> weights);
    void setSigmoid(bool sigmoid) { m_sigmoid = sigmoid; }
    vector<float> getWeights() { return m_weights; }
    bool getSigmoid() { return m_sigmoid; }
    
  private:
    float sigmoid(float x) { return (float) (1/(1+exp(-x))); }

};

#endif
