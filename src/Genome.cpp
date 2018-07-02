/*
    Copyright (c) 2016, 2017, 2018 Joao Salavisa <joao.salavisa@gmail.com>.

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

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "RandomUtil.h"
#include "Genome.h"

Genome::Genome(int n) {
  for(int i = 0; i < n; i++) {
    m_genes.push_back(RandomUtil::nextClampedFloat());
  }
  m_fitness = 0;
}

Genome::Genome(float fitness, vector<float> genes, bool muta) {
  m_fitness = fitness;
  m_genes = genes;
  
  if (muta) {
    mutate();
  }
}

Genome::Genome(float fitness, vector<float> genes) {
  m_fitness = fitness;
  m_genes = genes;
}

Genome * Genome::clone() {
  return new Genome(m_fitness, m_genes, false);
}

Genome * Genome::clone(bool mutate) {
  return new Genome(m_fitness, m_genes, mutate);
}

void Genome::mutate(float rate) {
  for(size_t i = 0; i < m_genes.size(); i++) {
    float rnd = RandomUtil::nextFloat();
    if (rnd < rate) {
      m_genes[i] = RandomUtil::nextClampedFloat();
    } 
  }
}

void Genome::mutate() {
  mutate(MUTATION_RATE);
}
