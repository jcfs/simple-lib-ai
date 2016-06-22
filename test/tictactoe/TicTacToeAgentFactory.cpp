#include "TicTacToeAgentFactory.h"
#include "TicTacToeAgent.h"

TicTacToeAgentFactory::TicTacToeAgentFactory() {

}

TicTacToeAgentFactory::~TicTacToeAgentFactory() {

}


Agent * TicTacToeAgentFactory::newInstance(Genome * genome, NetworkConfiguration * configuration) {
  return new TicTacToeAgent(genome, configuration);
}
