all: nn ga engine
	ar rcs ../build/libai.a *.o

nn: NeuralNetwork.cpp Neuron.cpp
	g++-7 -Wall -pedantic -c $^ -O3

ga: GeneticAlgorithm.cpp Genome.cpp
	g++-7 -Wall -pedantic -c $^ -O3

engine: Engine.cpp
	g++-7 -Wall -pedantic -c $^ -O3

clean:
	@rm -f *.o
	@rm -f ../build/libai.a

