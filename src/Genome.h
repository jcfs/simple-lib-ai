#ifndef GENOME_H
#define GENOME_H

#define MUTATION_RATE 0.30f

#include <vector>

using namespace std;

class Genome {
  private: 
    float m_fitness;
    vector<float> m_genes;

  public:
    /* constructors */
    Genome(int n);
    Genome(float fitness, vector<float> genes);
    Genome(float fitness, vector<float> genes, bool mutate);
    
    /* aux methods */
    Genome * clone();
    Genome * clone(bool mutate);
    void mutate();
    void mutate(float rate);

    /* getters/setters */
    vector<float> getGenes() { return m_genes; }
    void setGenes(vector<float> genes) { m_genes = genes; }
    float getFitness() { return m_fitness; }
    void setFitness(float fitness) { m_fitness = fitness; }
};

#endif
