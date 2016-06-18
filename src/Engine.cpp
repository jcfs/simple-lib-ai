#include <cstdio>
#include <list>

#include "Engine.h"
#include "GeneticAlgorithm.h"
#include "FitnessCalculator.h"

using namespace std;

Engine::Engine(int populationSize, NetworkConfiguration * configuration, FitnessCalculator * calculator) {
  // calculate the number of genes needed in the hidden layer
  // the number of inputs times the number of neurons per hidden player plus one (bias)
  int n_genes_hidden = configuration->getInputs()*(configuration->getNeuronHidden()+1);

  // calculate the number of genes needed in the output layer
  // the number of outputs times the number of neurons per hidden player plus one (bias)
  int n_genes_output = configuration->getOutputs()*(configuration->getNeuronHidden()+1);

  geneticAlgorithm = new GeneticAlgorithm(populationSize, n_genes_hidden + n_genes_output);
  m_configuration = configuration;
  m_calculator = calculator;
}

Engine::~Engine() {
  delete m_configuration;
  delete m_calculator;
  delete geneticAlgorithm;

  for(list<Agent *>::const_iterator it = activePopulation.begin(); it != activePopulation.end(); it++) {
    delete * it;
  }

  activePopulation.clear();
}

//update the engine
void Engine::update() { 
  if (isPopulationDead()) {
      for(list<Agent *>::const_iterator it = activePopulation.begin(); it != activePopulation.end(); it++) {
        m_calculator->calculate(*it);
      }
      geneticAlgorithm->breed();
      this->generateNewPopulation();
  } else {
    for(list<Agent *>::const_iterator it = activePopulation.begin(); it != activePopulation.end(); it++) {
      (*it)->update();
    }
  }
}


//
// private methods
//

bool Engine::isPopulationDead() {
  for(list<Agent *>::const_iterator it = activePopulation.begin(); it != activePopulation.end(); it++) {
    if ((*it)->isAlive()) {
      return false;
    }
  }

  return true;
}

void Engine::generateNewPopulation() {
  list<Genome *> population = geneticAlgorithm->getPopulation();

  for(list<Agent *>::const_iterator it = activePopulation.begin(); it != activePopulation.end(); it++) {
    delete *it;
  }
  activePopulation.clear();

  for(list<Genome *>::const_iterator it_g = population.begin(); it_g != population.end(); it_g++) {
    activePopulation.push_back(new Agent(*it_g, m_configuration));
  }
}

