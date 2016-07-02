#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "../../src/Engine.h"
#include "../../src/NetworkConfiguration.h"
#include "../../src/RandomUtil.h"


#include "BootStrapFitnessCalculator.h"
#include "BootStrapAgentFactory.h"

int main(int argc, char ** argv) {
  Engine * engine = new Engine(20, new NetworkConfiguration(9,1,40,9), new BootStrapFitnessCalculator(), new BootStrapAgentFactory(), NULL);

  delete engine;
}
