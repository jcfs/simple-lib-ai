#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

#include "TicTacToeAgent.h"
#include "TicTacToePerfectAgent.h"
#include "TicTacToeAgentFactory.h"
#include "TicTacToeFitnessCalculator.h"
#include "TicTacToeValidator.h"

#include "../../src/AgentFactory.h"
#include "../../src/Engine.h"
#include "../../src/NetworkConfiguration.h"
#include "../../src/RandomUtil.h"

int draw = 0;
int won = 0;
int lost = 0;

NeuralNetwork *m_network;

string to_s(char ch) {
  if (ch == BLANK)
    return string(" ");
  if (ch == CROSS)
    return string("X");
  if (ch == CIRCLE)
    return string("O");
}

string print_board(char *game) {
  string str;

  str.append(to_s(game[0]) + " | " + to_s(game[1]) + " | " +
      to_s(game[2]) + "\n");
  str.append("──┼───┼──\n");
  str.append(to_s(game[3]) + " | " + to_s(game[4]) + " | " +
      to_s(game[5]) + "\n");
  str.append("──┼───┼──\n");
  str.append(to_s(game[6]) + " | " + to_s(game[7]) + " | " +
      to_s(game[8]) + "\n");

  str.append("\n");

  return str;
}

int main(int argc, char **argv) {
  srand(time(0));

  vector < float >genes;
  std::ifstream fin(argv[1]);

  while (!fin.eof()) {
    double d;
    fin >> d;
    genes.push_back(d);
  }

  char game[9];

  NetworkConfiguration *config = new NetworkConfiguration(9, 1, 40, 9);
  m_network = new NeuralNetwork(config);
  m_network->loadWeights(genes);

  int win = 0, loss = 0, draw = 0;
  int k = 0;
  while (k++ < 100000) {
    for (int i = 0; i < 9; i++)
      game[i] = BLANK;

    int result = 0;
    while ((result = TicTacToeValidator::validate(game)) == NOT_OVER) {

      int move;
      do {
        move = rand() % 9;

      } while (game[move] != BLANK);

      game[move] = CIRCLE;

      if ((result = TicTacToeValidator::validate(game)) != NOT_OVER)
        break;

      vector < float >input;

      for (int i = 0; i < 9; i++) {
        input.push_back(game[i]);
      }

      vector < float >output = m_network->update(input);

      float max = -100;
      int mOutput = 0;

      for (int i = 0; i < output.size(); i++) {
        if (output[i] > max && game[i] == BLANK) {
          max = output[i];
          mOutput = i;
        }
      }
      game[mOutput] = CROSS;

    }

    if (result == CROSS) {
      win++;
    } else if (result == CIRCLE) {
      loss++;
    } else if (result == BLANK) {
      draw++;
    }
  }
  cout << "Average winning percentage after " << k << " games :" <<
    (double) (win + draw) / (win + loss + draw) * 100.0 << "\n";
}
