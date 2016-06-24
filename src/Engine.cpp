#include <fstream>
#include <cstdio>
#include <iostream>
#include <list>
#include <string>
#include <typeinfo>

#include "Engine.h"
#include "GeneticAlgorithm.h"
#include "FitnessCalculator.h"

using namespace std;

Engine::Engine(int populationSize, NetworkConfiguration * configuration, FitnessCalculator * calculator, AgentFactory * agentFactory, char * saveFilePath) {
  // calculate the number of genes needed in the hidden layer
  // the number of inputs times the number of neurons per hidden player plus one (bias)
  int n_genes_hidden = (configuration->getInputs()+1)*(configuration->getNeuronHidden());

  if (configuration->getHiddenLayers() > 1) {
    n_genes_hidden += (configuration->getNeuronHidden()+1) *configuration->getNeuronHidden()* (configuration->getHiddenLayers()-1);
  }

  // calculate the number of genes needed in the output layer
  // the number of outputs times the number of neurons per hidden player plus one (bias)
  int n_genes_output = configuration->getOutputs()*(configuration->getNeuronHidden()+1);

  geneticAlgorithm = new GeneticAlgorithm(populationSize, n_genes_hidden + n_genes_output);
  m_configuration = configuration;
  m_calculator = calculator;
  m_agentFactory = agentFactory;
  m_save_file_path = saveFilePath;
}

Engine::~Engine() {
  delete m_configuration;
  delete m_calculator;
  delete geneticAlgorithm;
  delete m_agentFactory;

  for(list<Agent *>::const_iterator it = activePopulation.begin(); it != activePopulation.end(); it++) {
    delete * it;
  }

  activePopulation.clear();
}

//update the engine
void Engine::update() { 
  if (isPopulationDead()) {
    // if all the population is dead we calculate their fitness
    // and breed a new population
    for(list<Agent *>::const_iterator it = activePopulation.begin(); it != activePopulation.end(); it++) {
      (*it)->getGenome()->setFitness(m_calculator->calculate(*it));
    }

    if (geneticAlgorithm->breed()) {
      cout << "Generation: " << geneticAlgorithm->getGeneration() << " size: (" << activePopulation.size() << ")\n";
      if (activePopulation.size() > 0) {
        activePopulation.sort(compareAgent);
        list<Agent *>::const_iterator it = activePopulation.begin();
        cout << "Fittest: " + (*it)->toString();

        ofstream myfile;
        myfile.open (m_save_file_path);

        for(size_t i = 0; i < (*it)->getGenome()->getGenes().size(); i++) {
          myfile << (*it)->getGenome()->getGenes()[i] << endl;
        }

        myfile.close();
      }
    }

    generateNewPopulation();
  } else {
    // if some of the agents are still alive in the active population
    // we update all that are still alive
    for(list<Agent *>::const_iterator it = activePopulation.begin(); it != activePopulation.end(); it++) {
      if ((*it)->isAlive()) {
        (*it)->update();
      }
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
    activePopulation.push_back(m_agentFactory->newInstance(*it_g, m_configuration));
  }
}

bool Engine::compareAgent(Agent * a, Agent * b) {
  return a->getGenome()->getFitness() > b->getGenome()->getFitness();
}
