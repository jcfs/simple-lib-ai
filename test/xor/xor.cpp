#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "../../src/NetworkConfiguration.h"
#include "../../src/NeuralNetwork.h"
#include "../../src/RandomUtil.h"

using namespace std;

int main(int argc, char ** argv) {
  
    srand (static_cast <unsigned> (time(0)));


  NetworkConfiguration * configuration = new NetworkConfiguration(2,1,4,1);
  NeuralNetwork * network = new NeuralNetwork(configuration);

  float input_r1[] = { 1.0 ,0.0 };
  vector<float> input1 (input_r1, input_r1 + sizeof(input_r1) / sizeof(float));
  float output_r1[] = { 1.0 };
  vector<float> output1 (output_r1, output_r1 + sizeof(output_r1) / sizeof(float));


  float input_r2[] = { 0.0 ,1.0 };
  vector<float> input2 (input_r2, input_r2 + sizeof(input_r2) / sizeof(float));
  float output_r2[] = { 1.0 };
  vector<float> output2 (output_r2, output_r2 + sizeof(output_r2) / sizeof(float));

  float input_r3[] = { 1.0 ,1.0 };
  vector<float> input3 (input_r3, input_r3 + sizeof(input_r3) / sizeof(float));
  float output_r3[] = { 0.0 };
  vector<float> output3 (output_r3, output_r3 + sizeof(output_r3) / sizeof(float));

  float input_r4[] = { 0.0 ,0.0 };
  vector<float> input4 (input_r4, input_r4 + sizeof(input_r4) / sizeof(float));
  float output_r4[] = { 0.0 };
  vector<float> output4 (output_r4, output_r4 + sizeof(output_r4) / sizeof(float));

  float error[4];
  
  while(true) {
    error[0] = network->train(input1, output1);
    error[1] = network->train(input2, output2);
    error[2] = network->train(input3, output3);
    error[3] = network->train(input4, output4);

    float max = 0;

    for(int i = 0; i < 4; i++) {
      if (error[i] > max) {
        max = error[i];
      }
    }

    if ((0.5-max) < 0.00005) {
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
