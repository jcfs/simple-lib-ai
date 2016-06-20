ttt-build: TickTackToeAgent.cpp TickTackToeAgentFactory.cpp TickTackToeFitnessCalculator.cpp main.cpp
	g++ -o ttt $^ -L../../build/. -lai -std=c++11

ttt-clean:
	rm main

all: ttt-build

clean: ttt-clean
