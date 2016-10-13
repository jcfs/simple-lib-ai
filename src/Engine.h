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

#ifndef ENGINE_H
#define ENGINE_H

#include "NetworkConfiguration.h"
#include "GeneticAlgorithm.h"
#include "FitnessCalculator.h"
#include "AgentFactory.h"
#include "Agent.h"

class Engine {
  private:
    GeneticAlgorithm * geneticAlgorithm;
    list<Agent *> activePopulation;
    NetworkConfiguration * m_configuration;
    FitnessCalculator * m_calculator;
    AgentFactory * m_agentFactory;
    char * m_save_file_path;
    double m_highest_fitness;

  public:
    Engine(int populationSize, NetworkConfiguration * configuration, FitnessCalculator * calculator, AgentFactory * agentFactory, char * sabeFilePath);
    ~Engine();
    
    // method that handles all the evolution logic
    // Generates a new population if needed 
    // Updates all the agents
    // calculate fitness for all of them
    // breeds a new population if needed
    void update();

  private:
    bool isPopulationDead();
    void generateNewPopulation();
    static bool compareAgent(Agent * a, Agent * b);
};


#endif
