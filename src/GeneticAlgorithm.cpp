/*
    Copyright (c) 2016, 2017 Joao Salavisa <joao.salavisa@gmail.com>.

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

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "RandomUtil.h"
#include "GeneticAlgorithm.h"
#include "Genome.h"

GeneticAlgorithm::GeneticAlgorithm(int population_size, int genes) {
  m_population_size = population_size;
  m_genes = genes;
  m_generation = 0;

  for(int i = 0; i < m_population_size; i++) {
    m_population.push_back(new Genome(genes));
  }
}

GeneticAlgorithm::GeneticAlgorithm(int population_size, vector<float> genes) {
  m_population_size = population_size;
  m_generation = 0;
  m_genes = genes.size();

  for(int i = 0; i < m_population_size; i++) {
    m_population.push_back(new Genome(m_genes, genes));
  }

}

// frees all the genome of the current population
GeneticAlgorithm::~GeneticAlgorithm() {
  for(list<Genome *>::const_iterator it = m_population.begin(); it != m_population.end(); it++) {
    delete (*it);
  }
}

bool GeneticAlgorithm::breed() {
  bool result = false;
  
  list<Genome *> new_population;
  list<Genome *> fittest = getFittest(2);

  Genome * father = fittest.front();

  if (father->getFitness() > m_current_fittest) {
    result = true;
  }

  m_current_fittest = father->getFitness();

  fittest.pop_front();
  Genome * mother = fittest.front();

  father->setFitness(0);
  new_population.push_back(father->clone());

  mother->setFitness(0);
  new_population.push_back(mother->clone()); 
  
  new_population.push_back(father->clone(true));
  new_population.push_back(mother->clone(true));

  // crossover the mother and the father for the rest of the population
  // and leave 2 empty slots for two totally new genes
  for(size_t i = new_population.size(); i < m_population.size() - 2; i++) {
    Genome * baby = crossOver(father, mother);
    baby->mutate();
    new_population.push_back(baby);
  }

  // two totally new genes
  new_population.push_back(new Genome(m_genes));
  new_population.push_back(new Genome(m_genes));

  // free all the unused genes
  list<Genome *>::const_iterator it = m_population.begin();
  for(int i = 0; it != m_population.end(); it++, i++) {
    delete (*it);
  }
  
  m_population.clear();

  m_population = new_population;

  // increment the generation
  m_generation++;

  return result;
}

Genome * GeneticAlgorithm::crossOver(Genome * father, Genome * mother) {
  vector<float> babyGenes;

  vector<float> fatherGenes = father->getGenes();
  vector<float> motherGenes = mother->getGenes();

  for(size_t i = 0; i < fatherGenes.size(); i++) {
    if (RandomUtil::nextBoolean()) {
      babyGenes.push_back(fatherGenes[i]);
    } else {
      babyGenes.push_back(motherGenes[i]);
    }
  }  

  return new Genome(0, babyGenes);
}

// get the fittest element of the current population
Genome * GeneticAlgorithm::getFittest() {
  list<Genome *> fittest = getFittest(1);
  return fittest.front();
}

// get the fittest n elements of the current population
list<Genome *> GeneticAlgorithm::getFittest(int n) {
  list<Genome *> result;

  if (n > m_population_size) {
    result = m_population;
  } else {
    m_population.sort(compareGenome);

    int i = 0;
    for(list<Genome *>::const_iterator iterator = m_population.begin(); iterator != m_population.end() && i < n; iterator++, i++) {
      result.push_back(*iterator);
    }
  }

  return result;
}

bool GeneticAlgorithm::compareGenome(Genome * a, Genome * b) {
  return a->getFitness() > b->getFitness();
}

