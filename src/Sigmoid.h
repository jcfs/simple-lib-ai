#ifndef SIGMOID_H
#define SIGMOID_H

#include <cmath>

class Sigmoid {
  public:
    static float sigmoid(float x) { return (float) (1/(1+exp(-x))); }
    static float dSigmoid(float x) { return (1 - x) * x; }

};


#endif
