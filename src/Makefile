objects: Genome.cpp Neuron.cpp GeneticAlgorithm.cpp NeuralNetwork.cpp Engine.cpp
	g++ -Wall -c $^
	ar rcs ../build/libai.a *.o

clean:
	@rm -f *.o
	@rm -f ../build/libai.a

