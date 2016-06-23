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

  m_network->importWeights(genome->getGenes());
}

// destructor we just need to destruct the neural network
TicTacToeAgent::~TicTacToeAgent() {
  delete m_network;
}

void TicTacToeAgent::update() {
  char game[9];

  for(int i = 0; i < 9; i++) {
    game[i] = BLANK;
  }

  draw = won = lost = 0;

  // we expand all the possible games with the current network
  // and count the number of draws/wins/losses
  expandTree(game);

  // and die, since this agent does not need more info
  die();
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
  for(size_t i = 0; i < m_genome->getGenes().size(); i++) {
    str.append(std::to_string(m_genome->getGenes()[i]));
    checkSum += m_genome->getGenes()[i];
    if (i+1 != m_genome->getGenes().size()) {
      str.append(", ");
    }
  }
  str.append("...] Checksum: " + to_string(checkSum) + " Fitness: " + to_string(m_genome->getFitness()) + "\n");
  str.append("won = " +to_string(won)+ " lost = " + to_string(lost) + " draw = " + to_string(draw) + "\n");
  str.append("\n");
  return str;
}

//
// Private Methods
//
void TicTacToeAgent::expandTree(char * currentGame) {

  // for every possible board
  for(int i = 0; i < 9; i++) {

    // if the current position is an empty slot
    if (currentGame[i] == BLANK) {
      currentGame[i] = CIRCLE;

      int result = TicTacToeValidator::validate(currentGame);
      if (result != NOT_OVER) {
        if (result == BLANK) {
          draw++;
        } else {
          lost++;
        }
        currentGame[i] = BLANK;

        // this current game is over, we can safely return after reseting the last play
        return;
      }

      vector<float> input;

      for(int i = 0; i < 9; i++) {
        input.push_back(currentGame[i]);
      }

      // feed the current game state to the neural network
      vector<float> output = m_network->update(input);

      float max = -1;
      int move = 0;

      // find the highest output that is an empty slot
      // and play there
      for(int i = 0; i < output.size(); i++) {
        if (output[i] > max && currentGame[i] == BLANK) {
          max = output[i];
          move = i;
        }
      }

      currentGame[move] = CROSS;

      result = TicTacToeValidator::validate(currentGame);
      if (result != NOT_OVER) {
        if (result == BLANK) {
          draw++;
        } else if (result == CROSS) {
          won++;
        }

        currentGame[move] = BLANK;
        currentGame[i] = BLANK;
        return;
      }
      expandTree(currentGame);
      currentGame[move] = BLANK;
      currentGame[i] = BLANK;
    }
  }

}

// Helper too string method
string TicTacToeAgent::to_s(char ch) {
  if (ch == BLANK) return string(" "); 
  if (ch == CROSS) return string("X"); 
  if (ch == CIRCLE) return string("O"); 
}
