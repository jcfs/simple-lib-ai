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

void GeneticAlgorithm::breed() {
  list<Genome *> new_population;
  list<Genome *> fittest = getFittest(2);

  Genome * father = fittest.front();
  fittest.pop_front();
  Genome * mother = fittest.front();

  father->setFitness(0);
  new_population.push_back(father);

  mother->setFitness(0);
  new_population.push_back(mother); 
  
  new_population.push_back(father->clone());
  new_population.push_back(mother->clone());

  for(int i = new_population.size(); i < m_population_size - 2; i++) {
    Genome * baby = crossOver(father, mother);
    baby->mutate();
    new_population.push_back(baby);
  }

  new_population.push_back(new Genome(m_genes));
  new_population.push_back(new Genome(m_genes));

  m_population = new_population;
  m_generation++;
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

Genome * GeneticAlgorithm::getFittest() {
  list<Genome *> fittest = getFittest(1);
  return fittest.front();
}


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

