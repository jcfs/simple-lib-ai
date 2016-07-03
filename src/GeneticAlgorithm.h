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
    ~GeneticAlgorithm();
    
    // breeds the current population into a new one
    // returns a boolean saying if a new fittest genome was found
    bool breed();

    // returns the fittest genome in the current population
    Genome * getFittest();

    // returns the nth fittest genomes in the current population
    list<Genome *> getFittest(int n);

    // return the current generation
    int getGeneration() { return m_generation; }

    // return the population
    list<Genome *> getPopulation() { return m_population; }

    double getCurrentFittest() { return m_current_fittest; }
    void setCurrentFittest(double current_fittest) { m_current_fittest = current_fittest; }
    
  private:
    Genome * crossOver(Genome * father, Genome * mother);
    static bool compareGenome(Genome * a, Genome * b);
};

#endif
