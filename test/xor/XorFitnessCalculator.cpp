#include <iostream>

#include "XorFitnessCalculator.h"
#include "XorAgent.h"

double XorFitnessCalculator::calculate(Agent * agent) {

	XorAgent * xAgent = (XorAgent *) agent;

  return 1/xAgent->getError();


}

