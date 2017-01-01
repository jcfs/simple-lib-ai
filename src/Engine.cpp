/*
    Copyright (c) 2016, 20172017 2017, 2017, 2016, 20172017 2017, 2017, 2016, 20172017 2017, 2017, 2016, 20172017 2017, 2017 Joao Salavisa <joao.salavisa@gmail.com>.

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software
    is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <fstream>
#include <cstdio>
#include <iostream>
#include <list>
#include <string>
#include <typeinfo>

#include "Util.h"
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

    if (activePopulation.size() > 0) {
      activePopulation.sort(compareAgent);
      list<Agent *>::const_iterator it = activePopulation.begin();

      if ((*it)->getGenome()->getFitness() > m_highest_fitness) {
        DEBUG("Generation: " << geneticAlgorithm->getGeneration() << " size: (" << activePopulation.size() << ")\n");
        DEBUG((*it)->toString());
        m_highest_fitness = (*it)->getGenome()->getFitness();

        if (m_save_file_path != NULL) {
          ofstream save_file;
          save_file.open(m_save_file_path);
          save_file << m_configuration->getInputs() << " " << m_configuration->getHiddenLayers() << " " << m_configuration->getNeuronHidden() << " " << m_configuration->getOutputs() << endl;

          for(size_t i = 0; i < (*it)->getGenome()->getGenes().size(); i++) {
            save_file << (*it)->getGenome()->getGenes()[i] << endl;
          }

          save_file.close();
        }
      }
    }

    // lets breed a new population in the GA
    geneticAlgorithm->breed();
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
  for(list<Agent *>::const_iterator it = activePopulation.begin(); it != activePopulation.end(); it++) {
    delete *it;
  }
  activePopulation.clear();

  list<Genome *> population = geneticAlgorithm->getPopulation();
  for(list<Genome *>::const_iterator it_g = population.begin(); it_g != population.end(); it_g++) {
    activePopulation.push_back(m_agentFactory->newInstance(*it_g, m_configuration));
  }
}

bool Engine::compareAgent(Agent * a, Agent * b) {
  return a->getGenome()->getFitness() > b->getGenome()->getFitness();
}
