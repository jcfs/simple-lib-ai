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

  public:
    Engine(int populationSize, NetworkConfiguration * configuration, FitnessCalculator * calculator, AgentFactory * agentFactory);
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
};


#endif
