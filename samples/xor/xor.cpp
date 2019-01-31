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

float r_min(float * array, size_t size) {
  float min = FLT_MIN_EXP;

  for(size_t i = 0; i < size; i++) {
    if (array[i] > min) {
      min = array[i];
    }
  }

  return min;
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

  NetworkConfiguration * configuration = new NetworkConfiguration(2,1,16,1);
  NeuralNetwork * network = new NeuralNetwork(configuration);

  network->init();

  vector<float> input1 = gen_vector(2, 1.0, 0.0);
  vector<float> input2 = gen_vector(2, 0.0, 1.0);
  vector<float> input3 = gen_vector(2, 1.0, 1.0);
  vector<float> input4 = gen_vector(2, 0.0, 0.0);

  vector<float> output1 = gen_vector(1, 1.0);
  vector<float> output2 = gen_vector(1, 1.0);
  vector<float> output3 = gen_vector(1, 0.0);
  vector<float> output4 = gen_vector(1, 0.0);

  float error[4];
  int iterations = 0;
  while(true) {
    error[0] = network->train(input1, output1);
    error[1] = network->train(input2, output2);
    error[2] = network->train(input3, output3);
    error[3] = network->train(input4, output4);

    float max = r_min(error, 4);

    if (max < 0.0005) {
      break;
    }

    iterations++;
    cout << "Current output: " << iterations << endl;
    vector<float> o = network->feedForward(input1);
    cout << "1, 0 => " << roundf(o[0]*100) / 100 << endl;

    o = network->feedForward(input2);
    cout << "0, 1 => " << roundf(o[0]*100) / 100 << endl;

    o = network->feedForward(input3);
    cout << "1, 1 => " << roundf(o[0]*100) / 100 << endl;

    o = network->feedForward(input4);
    cout << "0, 0 => " << roundf(o[0]*100) / 100 << endl;
  }
}
