#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <list>

#include "Genome.h"

using namespace std;

class GeneticAlgorithm {

  private:
    list<Genome *> m_population;
    int m_population_size;
    int m_genes;
    int m_generation;

  public:
    GeneticAlgorithm(int population_size, int genes);
    GeneticAlgorithm(int population_size, vector<float> genes);
    
    void breed();
    Genome * getFittest();
    list<Genome *> getFittest(int n);
    int getGeneration() { return m_generation; }
    list<Genome *> getPopulation() { return m_population; }
    
  private:
    Genome * crossOver(Genome * father, Genome * mother);
    static bool compareGenome(Genome * a, Genome * b);
};

#endif
