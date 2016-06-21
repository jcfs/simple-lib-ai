#include <iostream>
#include <string>

#include "../../src/Util.h"
#include "TickTackToeAgent.h"

TickTackToeAgent::TickTackToeAgent(Genome * genome, NetworkConfiguration * configuration) {
  m_network = new NeuralNetwork(configuration);
  m_genome = genome;
  m_alive = true;

  for(int i = 0; i < 3; i++) 
    for(int j = 0; j < 3; j++) 
      game[i][j] = 3; 
}

TickTackToeAgent::~TickTackToeAgent() {
  delete m_network;
}

void TickTackToeAgent::update() {
  vector<float> input;

  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++) {
      input.push_back(game[i][j]);
    }

  vector<float> output = m_network->update(input);

  float out = output[0];

  // output between 0-8
  int mOutput = round(8.0 * out);

  int x = mOutput / 3;
  int y = mOutput % 3;

  if (game[x][y] != BLANK) {
    m_alive = false;
  } else {
    game[x][y] = CROSS;

    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        if (game[i][j] == 3) {
          game[i][j] = CIRCLE;
          i=10;
          break;
        }
      }
    }

    bool over = true;

    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        if (game[i][j] == BLANK) over = false;
      }
    }

    if (over) {
      m_alive = false;
    }

  }
    cout << toString();
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
  for(size_t i = 0; i < 3; i++) {
    str.append(std::to_string(m_genome->getGenes()[i]));
    if (i+1 != m_genome->getGenes().size()) {
      str.append(", ");
    }
  }
  str.append("...]\n");

  for(int i = 0; i < 3; i++) {
    str.append("\n");
    for(int j = 0; j < 3; j++) {
      if (game[i][j] == BLANK) {
        str.append("_");
      } else {
        str.append(std::to_string(game[i][j]));
      }
    }
  }

  str.append("\n");
  return str;
}
