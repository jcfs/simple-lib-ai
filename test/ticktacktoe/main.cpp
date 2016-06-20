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

  NetworkConfiguration * config = new NetworkConfiguration(10,1,30,1);
  AgentFactory * factory = new TickTackToeAgentFactory();
  Engine * engine = new Engine(2, config, new TickTackToeFitnessCalculator(), factory);

  engine->update();
  engine->update();

}
