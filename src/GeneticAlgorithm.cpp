#include <cstdlib>
#include <ctime>

#include "RandomUtil.h"
#include "GeneticAlgorithm.h"
#include "Genome.h"

GeneticAlgorithm::GeneticAlgorithm.h(int population_size, int genes) {
  m_population_size = population_size;
  m_genes = genes;
  m_generation = 0;

  for(int i = 0; i < m_population_size; i++) {
    m_population.push_back(new Genome(genes));
  }
}

GeneticAlgorithm::GeneticAlgorithm.h(int population_size, vector<float> genes) {
  
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


  new_population.push_back(father);
  new_population.push_back(mother); 
  


}
