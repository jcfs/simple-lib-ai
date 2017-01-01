/*
    Copyright (c) 2016, 2017 Joao Salavisa <joao.salavisa@gmail.com>.

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software
    is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
