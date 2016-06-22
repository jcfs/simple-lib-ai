ttt-build: TicTacToeAgent.cpp TicTacToeAgentFactory.cpp TicTacToeFitnessCalculator.cpp main.cpp TicTacToeValidator.cpp
	g++ -o ttt $^ -L../../build/. -lai -std=c++11

ttt-clean:
	rm -f main ttt

all: ttt-build

clean: ttt-clean
