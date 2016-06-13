#ifndef GENOME_H
#define GENOME_H

#define MUTATION_RATE 0.20f

class Genome {
  private: 
    float m_fitness;
    float * m_genes;
    int m_gene_size;

  public:
    /* constructors */
    Genome(int n);
    Genome(float fitness, float * genes, int gene_size);
    Genome(float fitness, float * genes, int gene_size, bool mutate);
    
    /* aux methods */
    Genome * clone();
    void mutate();
    void mutate(float rate);

    /* getters/setters */
    float * getGenes() { return m_genes; }
    void setGenes(float * genes) { m_genes = genes; }
    float getFitness() { return m_fitness; }
    void setFitness(float fitness) { m_fitness = fitness; }
};

#endif
