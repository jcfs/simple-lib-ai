ttt-build: TicTacToeAgent.cpp TicTacToeAgentFactory.cpp TicTacToeFitnessCalculator.cpp main.cpp TicTacToeValidator.cpp TicTacToePerfectAgent.cpp
	g++ -o ttt $^ -L../../build/. -lai -std=c++11 -O3

ttt-tester: TicTacToeAgent.cpp TicTacToeAgentFactory.cpp TicTacToeFitnessCalculator.cpp tester.cpp TicTacToeValidator.cpp TicTacToePerfectAgent.cpp
	g++ -o tester $^ -L../../build/. -lai -std=c++11 -O3

ttt-clean:
	rm -f main ttt

all: ttt-build

clean: ttt-clean
