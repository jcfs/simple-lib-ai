#include <cstdlib>
#include <ctime>

#include "Genome.h"

Genome::Genome(int n) {

  m_gene_size = n;
  m_genes = (float *) calloc(n, sizeof(float));

  for(int i = 0; i < n; i++) {
    srand (static_cast <unsigned> (time(0)));
    m_genes[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
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
  srand (static_cast <unsigned> (time(0)));

  for(int i = 0; i < m_gene_size; i++) {
    float rnd = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if (rnd < rate) {
      m_genes[i] *= static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }
  }
}

void Genome::mutate() {
  mutate(MUTATION_RATE);
}
