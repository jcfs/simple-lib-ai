all: nn ga engine
	ar rcs ../build/libai.a *.o

nn: NeuralNetwork.cpp Neuron.cpp
	$(CXX) -Wall -pedantic -std=c++11 -c $^ -O3 

ga: GeneticAlgorithm.cpp Genome.cpp
	$(CXX) -Wall -pedantic -std=c++11 -c $^ -O3

engine: Engine.cpp
	$(CXX) -Wall -pedantic -std=c++11 -c $^ -O3

clean:
	@rm -f *.o
	@rm -f ../build/libai.a

