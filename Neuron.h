#ifndef NEURON_H
#define NEURON_H

class Neuron {
  private:
    float * m_weights;
    bool m_sigmoid = true;

  public:
    /* constructors */
    Neuron(int inputs);
    Neuron(Neuron &neuron);
    float evaluate(float * inputs);
    
    /* getters/setters */
    void setWeights(float * weights) { m_weights = weights; }
    void setSigmoid(bool sigmoid) { m_sigmoid = sigmoid; }
    float * getWeights() { return m_weights; }
    
  private:
    float sigmoid(float x) { return (float) (1/(1+exp(-x))); }

};

#endif
