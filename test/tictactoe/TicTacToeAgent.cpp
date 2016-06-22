#include <iostream>
#include <string>

#include "../../src/Util.h"
#include "TicTacToeAgent.h"
#include "TicTacToeValidator.h"
#include "TicTacToePerfectAgent.h"

TicTacToeAgent::TicTacToeAgent(Genome * genome, NetworkConfiguration * configuration) {
  m_network = new NeuralNetwork(configuration);
  m_genome = genome;
  m_alive = true;

  for(int i = 0; i < 9; i++) {
      game[i] = BLANK; 
  }

  m_network->importWeights(genome->getGenes());
}

TicTacToeAgent::~TicTacToeAgent() {
  delete m_network;
}

void TicTacToeAgent::update() {
  vector<float> input;

  game[TicTacToePerfectAgent::play(game, CIRCLE)] = CIRCLE;
  m_alive = TicTacToeValidator::validate(game) == NOT_OVER;

  if (!m_alive) {
    return;
  }

  for(int i = 0; i < 9; i++) {
    input.push_back(game[i]);
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
  game[mOutput] = CROSS;

  m_alive = TicTacToeValidator::validate(game) == NOT_OVER;
}

bool TicTacToeAgent::isAlive() {
  return m_alive;
}

bool TicTacToeAgent::isDead() {
  return !m_alive;
}

void TicTacToeAgent::die() {
  m_alive = false;
}

string TicTacToeAgent::toString() {
  string str = "TicTacToeAgent: ";

  str.append("status=" + (m_alive ? to_string(1) : to_string(0)));
  str.append(" Genome: [");

  double checkSum = 0;
  for(size_t i = 0; i < 10; i++) {
    str.append(std::to_string(m_genome->getGenes()[i]));
    checkSum += m_genome->getGenes()[i];
    if (i+1 != m_genome->getGenes().size()) {
      str.append(", ");
    }
  }
  str.append("...] Checksum: " + to_string(checkSum) + " Fitness: " + to_string(m_genome->getFitness()) + "\n");

  str.append(to_s(game[0]) + " | " + to_s(game[1]) + " | " + to_s(game[2]) + "\n"); 
  str.append("──┼───┼──\n");
  str.append(to_s(game[3]) + " | " + to_s(game[4]) + " | " + to_s(game[5]) + "\n"); 
  str.append("──┼───┼──\n");
  str.append(to_s(game[6]) + " | " + to_s(game[7]) + " | " + to_s(game[8]) + "\n"); 


  str.append("\n");

  return str;
}

string TicTacToeAgent::to_s(char ch) {

  if (ch == BLANK) return string(" "); 
  if (ch == CROSS) return string("X"); 
  if (ch == CIRCLE) return string("O"); 

}
