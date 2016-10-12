xor-build: xor.cpp XorFitnessCalculator.cpp XorAgent.cpp XorFitnessCalculator.cpp XorAgentFactory.cpp
	g++ -o xor $^ -L../../build/. -lai -std=c++11 -O3

xor-clean:
	rm -f xor

clean: xor-clean

all: xor-build
