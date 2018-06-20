#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cfloat>
#include <cstdarg>

#include "../../src/NetworkConfiguration.h"
#include "../../src/NeuralNetwork.h"

using namespace std;

vector<float> gen_vector(int n_args, ...) {
  vector<float> result;
  
  va_list ap;
  va_start(ap, n_args);

  for(int i = 0; i < n_args; i++) {
    result.push_back((float) va_arg(ap, double));
  }

  va_end(ap);

  return result;
}

// tests a forward pass for a well known scenario and verifies that the output is calculated 
// correctly
void test_forward_pass(NeuralNetwork * network, vector<float> input, vector<float> weights) {
  network->loadWeights(weights);
  vector<float> output = network->feedForward(input);

  float o1 = output[0];
  float o2 = output[1];

  if (output[0] != 0.75136507f || output[1] != 0.772928465f) {
    cout << "test_forward_pass - FAILED";
    exit(1);
  } else {
    cout << "test_forward_pass - PASSED";
  }
}

int main(int argc, char ** argv) {
  srand (static_cast <unsigned> (time(0)));

  NetworkConfiguration * configuration = new NetworkConfiguration(2,1,2,2);
  NeuralNetwork * network = new NeuralNetwork(configuration);

  vector<float> w = gen_vector(12, 0.15f, 0.2f, 0.35f, 0.25, 0.30, 0.35, 0.40, 0.45, 0.60, 0.50, 0.55, 0.60);
  vector<float> input = gen_vector(2, 0.05, 0.1);

  test_forward_pass(network, input, w);
}
