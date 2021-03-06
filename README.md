## Neural Network - Genetic Algorithm - C++ Implementation

[![Build Status](https://travis-ci.org/jcfs/simple-lib-ai.svg?branch=master)](https://travis-ci.org/jcfs/simple-lib-ai)

(work in progress)

This project is still a work in progress and pretends to create an implementation of an Engine capable of genetically evolve AI agents that contain a feedforward neural network.

All of project main structures are independent and self contained, meaning that the neural network and genetic algorithm systems are not tightly coupled.

### Directory Structure
```
  ├── bin             - executable bin folder
  ├── build           - default ai lib build folder
  ├── src             - ai lib source folder
  ├── test            - ai lib tests folder
      └── memory      - memory source code
  └── sample          - samples source folder
      ├── xor         - xor agent to solve XOR function
      └── tictactoe   - tic tac toe agent example source code
```
### How to build the library
```
  nn-ga$ make
  make -C src/ objects
  make[1]: Entering directory 'nn-ga/src'
  g++ -Wall -c Genome.cpp Neuron.cpp GeneticAlgorithm.cpp NeuralNetwork.cpp Engine.cpp -O3
  ar rcs ../build/libai.a *.o
  make[1]: Leaving directory 'nn-ga/src'
```
The lib file (libai.a) was built to the build/ directory and can be linked from now on with any of your projects. In the test/ folder several examples can be found on how to link the lib, and how to use it on your own agents.

### Core Source Structures

#### Neural Network

#### Genetic Algorithm

#### Engine

### Proof of Concept
The XOR example implements a a XOR agent using a feedforward neural network to derive the XOR function. After a couple million iterations it converges to the desired output:

```
Current output: 2152738
1, 0 => 0.93
0, 1 => 0.93
1, 1 => 0.07
0, 0 => 0.07
```

The implementation is suboptimal since it is not using backpropagation yet.
