#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

#include "../../src/NetworkConfiguration.h"
#include "../../src/NeuralNetwork.h"

NeuralNetwork *m_network;

int main(int argc, char **argv) {
  srand(time(0));

  vector < float >genes;
  std::ifstream fin(argv[1]);

  int input_size;
  int hidden_layers;
  int hidden_neurons;
  int output_size;

  fin >> input_size;
  fin >> hidden_layers;
  fin >> hidden_neurons;
  fin >> output_size;

  cout << "Loaded network: " << input_size << " " << hidden_layers << " " << hidden_neurons << " " << output_size << endl;  

  while (!fin.eof()) {
    double d;
    fin >> d;
    genes.push_back(d);
  }

  char game[9];

  NetworkConfiguration *config = new NetworkConfiguration(input_size, hidden_layers, hidden_neurons, output_size);
  m_network = new NeuralNetwork(config);
  m_network->loadWeights(genes);

  for(float i = 0; i < 3.15; i+=0.01) {
    vector <float> input;
    input.push_back(i);
    vector <float> output = m_network->feedForward(input);

    cout << output[0] << endl;
  }

}
