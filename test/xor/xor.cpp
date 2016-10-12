#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "../../src/Engine.h"
#include "../../src/NetworkConfiguration.h"
#include "../../src/RandomUtil.h"


#include "XorFitnessCalculator.h"
#include "XorAgentFactory.h"

int main(int argc, char ** argv) {

	srand (static_cast <unsigned> (time(0)));

  if (argc < 3 || atoi(argv[1]) < 4) {
    cerr << "Usage: ./xor <population_size> <agent_save_file> (population_size >= 4)" << endl;
    exit(1);
  }

 	NetworkConfiguration * config = new NetworkConfiguration(2,1,10,1);
  AgentFactory * factory = new XorAgentFactory();

  Engine * engine = new Engine(atoi(argv[1]), config, new XorFitnessCalculator(), factory, argv[2]);
  while(true) {
    engine->update();
  }

  delete engine;

}
