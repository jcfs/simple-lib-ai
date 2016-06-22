#include <cstdlib>
#include <ctime>
#include <iostream>

#include "RandomUtil.h"
#include "Genome.h"

Genome::Genome(int n) {
  for(int i = 0; i < n; i++) {
    m_genes.push_back(RandomUtil::nextClampedFloat());
  }
  m_fitness = 0;
}

Genome::Genome(float fitness, vector<float> genes, bool muta) {
  m_fitness = fitness;
  m_genes = genes;
  
  if (muta) {
    mutate();
  }
}

Genome::Genome(float fitness, vector<float> genes) {
  m_fitness = fitness;
  m_genes = genes;
}

Genome * Genome::clone() {
  return new Genome(m_fitness, m_genes, true);
}

void Genome::mutate(float rate) {
  for(size_t i = 0; i < m_genes.size(); i++) {
    float rnd = RandomUtil::nextFloat();
    if (rnd < rate) {
      m_genes[i] = RandomUtil::nextClampedFloat();
    } 
  }
}

void Genome::mutate() {
  mutate(MUTATION_RATE);
}
