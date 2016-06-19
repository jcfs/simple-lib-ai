#include <cstdlib>
#include <ctime>

#include "RandomUtil.h"
#include "Genome.h"

Genome::Genome(int n) {
  for(int i = 0; i < n; i++) {
    m_genes.push_back(RandomUtil::nextClampedFloat());
  }
}

Genome::Genome(float fitness, vector<float> genes, bool mutate) {
  m_fitness = fitness;
  m_genes = genes;
  
  if (mutate) {
    Genome::mutate();
  }
}

Genome::Genome(float fitness, vector<float> genes) {
  m_fitness = fitness;
  m_genes = genes;
}

Genome * Genome::clone() {
  return new Genome(m_fitness, m_genes);
}

void Genome::mutate(float rate) {
  for(size_t i = 0; i < m_genes.size(); i++) {
    float rnd = RandomUtil::nextClampedFloat();
    if (rnd < rate) {
      m_genes[i] *= RandomUtil::nextClampedFloat();
    }
  }
}

void Genome::mutate() {
  mutate(MUTATION_RATE);
}
