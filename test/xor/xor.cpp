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

float r_max(float * array, size_t size) {
  float max = FLT_MIN_EXP;

  for(size_t i = 0; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
    }
  }

  return max;
}

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

int main(int argc, char ** argv) {
  
  srand (static_cast <unsigned> (time(0)));

  NetworkConfiguration * configuration = new NetworkConfiguration(2,1,4,1);
  NeuralNetwork * network = new NeuralNetwork(configuration);


  vector<float> input1 = gen_vector(2, 1.0, 0.0);
  vector<float> input2 = gen_vector(2, 0.0, 1.0);
  vector<float> input3 = gen_vector(2, 1.0, 1.0);
  vector<float> input4 = gen_vector(2, 0.0, 0.0);

  vector<float> output1 = gen_vector(1, 1.0);
  vector<float> output2 = gen_vector(1, 1.0);
  vector<float> output3 = gen_vector(1, 0.0);
  vector<float> output4 = gen_vector(1, 0.0);

  float error[4];

  while(true) {
    error[0] = network->train(input1, output1);
    error[1] = network->train(input2, output2);
    error[2] = network->train(input3, output3);
    error[3] = network->train(input4, output4);

    float max = r_max(error, 4);

    if (max < 0.00005) {
      break;
    }

    cout << "error: " << max << endl;
  }

  vector<float> o = network->feedForward(input1);
  cout << roundf(o[0]*100) / 100 << endl;

  o = network->feedForward(input2);
  cout << roundf(o[0]*100) / 100 << endl;

  o = network->feedForward(input3);
  cout << roundf(o[0]*100) / 100 << endl;

  o = network->feedForward(input4);
  cout << roundf(o[0]*100) / 100 << endl;
}
