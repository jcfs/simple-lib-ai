#include "Engine.h"
#include "GeneticAlgorithm.h"

using namespace std;

Engine::Engine(int populationSize, NetworkConfiguration configuration) {
  // calculate the number of genes needed in the hidden layer
  // the number of inputs times the number of neurons per hidden player plus one (bias)
  int n_genes_hidden = configuration.getInputs()*(configuration.getNeuronHidden()+1);

  // calculate the number of genes needed in the output layer
  // the number of outputs times the number of neurons per hidden player plus one (bias)
  int n_genes_output = configuration.getOutputs()*(configuration.getNeuronHidden()+1);

  geneticAlgorithm = new GeneticAlgorithm(populationSize, n_genes_hidden + n_genes_output);
  m_configuration = configuration;
}

Engine::update() { 

  if (isPopulationDead()) {
      generateNewPopulation();
  }
}


//
// private methods
//

bool Engine::isPopulationDead() {
  list<Agent *>::const_iter it;

  for(it = activePopulation.begin(); it != activePopulation.end(); it++) {
    if (*it != NULL && (*it)->isAlive()) {
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

  for(list<Genome *>::const_iterator it_g = population.begin; it_g != population.end(); it_g++) {
    Agent * agent = new Agent(*it_g, configuration);
    activePopulation.push_back(agent);
  }
}

