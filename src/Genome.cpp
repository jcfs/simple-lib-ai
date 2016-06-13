#include <cstdlib>
#include <ctime>

#include "RandomUtil.h"
#include "Genome.h"

Genome::Genome(int n) {

  m_gene_size = n;
  m_genes = (float *) calloc(n, sizeof(float));

  for(int i = 0; i < n; i++) {
    m_genes[i] = RandomUtil::nextClampedFloat();
  }
}

Genome::Genome(float fitness, float * genes, int gene_size, bool mutate) {
  m_fitness = fitness;
  m_genes = genes;
  m_gene_size = gene_size;
  
  if (mutate) {
    Genome::mutate();
  }
}

Genome::Genome(float fitness, float * genes, int gene_size) {
  m_fitness = fitness;
  m_genes = genes;
  m_gene_size = gene_size;
}

Genome * Genome::clone() {
  return new Genome(m_fitness, m_genes, m_gene_size);
}

void Genome::mutate(float rate) {
  for(int i = 0; i < m_gene_size; i++) {
    float rnd = RandomUtil::nextClampedFloat();
    if (rnd < rate) {
      m_genes[i] *= RandomUtil::nextClampedFloat();
    }
  }
}

void Genome::mutate() {
  mutate(MUTATION_RATE);
}
