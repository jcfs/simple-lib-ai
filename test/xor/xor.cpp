#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "../../src/NetworkConfiguration.h"
#include "../../src/NeuralNetwork.h"
#include "../../src/RandomUtil.h"

using namespace std;

int main(int argc, char ** argv) {
  

  NetworkConfiguration * configuration = new NetworkConfiguration(2,1,10,1);
  NeuralNetwork * network = new NeuralNetwork(configuration);

  float input1[] = { 1.0 ,0.0 };
  vector<float> input (input1, input1 + sizeof(input1) / sizeof(float));

  float output1[] = { 1.0 };
  vector<float> output (output1, output1 + sizeof(output) / sizeof(float));

  while(true) {
    float error = network->train(input, output);
    cout << error << endl;
  }


}
