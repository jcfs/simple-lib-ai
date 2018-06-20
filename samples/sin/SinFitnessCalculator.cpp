#include <iostream>

#include "SinFitnessCalculator.h"
#include "SinAgent.h"

double SinFitnessCalculator::calculate(Agent * agent) {
  SinAgent * sAgent = (SinAgent *) agent;
  
  return 1/sAgent->getError();
}

