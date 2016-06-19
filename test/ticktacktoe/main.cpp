#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "TickTackToeAgent.h"
#include "../../src/NetworkConfiguration.h"
#include "../../src/RandomUtil.h"

int main(int argc, char ** argv) {
  srand (static_cast <unsigned> (time(0)));

  TickTackToeAgent * agent = new TickTackToeAgent(new Genome(10), new NetworkConfiguration(10,2,10,2));
  cout << agent->toString();
  agent->update();
  cout << agent->toString();
}
