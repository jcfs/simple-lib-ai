#include <iostream>
#include <string>

#include "../../src/Util.h"
#include "TickTackToeAgent.h"

TickTackToeAgent::TickTackToeAgent(Genome * genome, NetworkConfiguration * configuration) {
  m_network = new NeuralNetwork(configuration);
  m_genome = genome;
  m_alive = true;

  for(int i = 0; i < 9; i++) {
      game[i] = BLANK; 
  }

  m_network->importWeights(genome->getGenes());
}

TickTackToeAgent::~TickTackToeAgent() {
  delete m_network;
}

void TickTackToeAgent::update() {
  vector<float> input;

  int empty = 0;
  
  for(int i = 0; i < 9; i++) {
    if (game[i] == CROSS) {
      input.push_back(1);
      input.push_back(0);
    } else if (game[i] == CIRCLE) {
      input.push_back(0);
      input.push_back(1);
    } else {
      input.push_back(0);
      input.push_back(0);
      empty++;
    }
  }

  vector<float> output = m_network->update(input);

  float max = -100;
  int mOutput = 0;

  for(int i = 0; i < output.size(); i++) {
    if (output[i] > max && game[i] == BLANK) {
      max = output[i];
      mOutput = i;
    }
  }


  if (game[mOutput] != BLANK || empty == 1) {
    m_alive = false;
  } else {
    game[mOutput] = CROSS;

    int move;
    do
    {
      move  = rand() % 9;     // just pick a random number
    }
    while (move < 0 || move > 8 || game[move] != BLANK);
    game[move] = CIRCLE;


    bool over = true;

    for(int i = 8; i >= 0; i--) {
      if (game[i] == BLANK) over = false;
    }

    if (over) {
      m_alive = false;
    }

  }
}

bool TickTackToeAgent::isAlive() {
  return m_alive;
}

bool TickTackToeAgent::isDead() {
  return !m_alive;
}

void TickTackToeAgent::die() {
  m_alive = false;
}

string TickTackToeAgent::toString() {
  string str = "TickTackToeAgent: ";

  str.append("status=" + (m_alive ? to_string(1) : to_string(0)));
  str.append(" Genome: [");
  for(size_t i = 0; i < 5; i++) {
    str.append(std::to_string(m_genome->getGenes()[i]));
    if (i+1 != m_genome->getGenes().size()) {
      str.append(", ");
    }
  }
  str.append("...] Fitness: " + to_string(m_genome->getFitness()) + "\n");

  str.append(to_s(game[0]) + " | " + to_s(game[1]) + " | " + to_s(game[2]) + "\n"); 
  str.append("──┼───┼──\n");
  str.append(to_s(game[3]) + " | " + to_s(game[4]) + " | " + to_s(game[5]) + "\n"); 
  str.append("──┼───┼──\n");
  str.append(to_s(game[6]) + " | " + to_s(game[7]) + " | " + to_s(game[8]) + "\n"); 


  str.append("\n");

  return str;
}

string TickTackToeAgent::to_s(char ch) {

  if (ch == BLANK) return string(" "); 
  if (ch == CROSS) return string("X"); 
  if (ch == CIRCLE) return string("O"); 

}
