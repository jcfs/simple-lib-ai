#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "../../src/Engine.h"
#include "../../src/NetworkConfiguration.h"
#include "../../src/RandomUtil.h"


#include "MemoryFitnessCalculator.h"
#include "MemoryAgentFactory.h"

int main(int argc, char ** argv) {
  Genome * genome = new Genome(500);
  genome->mutate();
  delete genome;

  GeneticAlgorithm * g = new GeneticAlgorithm(20, 500);
  g->breed();
  delete g;


  Engine * engine = new Engine(20, new NetworkConfiguration(9,1,40,9), new MemoryFitnessCalculator(), new MemoryAgentFactory(), NULL);

  engine->update();
  engine->update();
  engine->update();
  engine->update();
  engine->update();

  delete engine;
  
}
