/*
    Copyright (c) 2016 Joao Salavisa <joao.salavisa@gmail.com>.

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
