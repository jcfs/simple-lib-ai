memory-build: memory.cpp MemoryFitnessCalculator.cpp MemoryAgent.cpp MemoryFitnessCalculator.cpp MemoryAgentFactory.cpp
	g++ -o memory $^ -L../../build/. -lai -std=c++11 -O3

memory-clean:
	rm -f memory

all: memory-build

clean: memory-clean

