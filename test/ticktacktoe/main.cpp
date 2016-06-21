#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "TickTackToeAgent.h"
#include "TickTackToeAgentFactory.h"
#include "TickTackToeFitnessCalculator.h"

#include "../../src/AgentFactory.h"
#include "../../src/Engine.h"
#include "../../src/NetworkConfiguration.h"
#include "../../src/RandomUtil.h"

int main(int argc, char ** argv) {
  srand (static_cast <unsigned> (time(0)));

  NetworkConfiguration * config = new NetworkConfiguration(18,1,20,9);
  AgentFactory * factory = new TickTackToeAgentFactory();
  Engine * engine = new Engine(atoi(argv[1]), config, new TickTackToeFitnessCalculator(), factory);

  while(true) {
    engine->update();
  }
}
