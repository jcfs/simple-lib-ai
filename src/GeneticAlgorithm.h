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
    double m_current_fittest;

  public:
    GeneticAlgorithm(int population_size, int genes);
    GeneticAlgorithm(int population_size, vector<float> genes);
    
    bool breed();
    Genome * getFittest();
    list<Genome *> getFittest(int n);
    int getGeneration() { return m_generation; }
    list<Genome *> getPopulation() { return m_population; }

    double getCurrentFittest() { return m_current_fittest; }
    void setCurrentFittest(double current_fittest) { m_current_fittest = current_fittest; }
    
  private:
    Genome * crossOver(Genome * father, Genome * mother);
    static bool compareGenome(Genome * a, Genome * b);
};

#endif
