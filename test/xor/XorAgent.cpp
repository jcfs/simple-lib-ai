#include <iostream>
#include <string>
#include <cstring>

#include "../../src/Util.h"
#include "XorAgent.h"

XorAgent::XorAgent(Genome * genome, NetworkConfiguration * configuration) {
	m_network = new NeuralNetwork(configuration);
	m_genome = genome;
	m_alive = true;
}

// destructor we just need to destruct the neural network
XorAgent::~XorAgent() {
	delete m_network;
}

void XorAgent::update() {
	m_error = 1;

	char values[4][2] = {
		{0,0},
		{0,1},
		{1,1},
		{1,0}
	};

	for(int i = 0; i < 4; i++) {
		vector<float> input;
		input.push_back(values[i][0]);
		input.push_back(values[i][1]);
		vector<float> output = m_network->feedForward(input);

		int v_xor = (int) round(output[0]);

		if ((values[i][0] ^ values[i][1]) != v_xor) {
			m_error++;
		} else {
			m_error--;
		}
	}

	m_alive = false;
}

string XorAgent::toString() {
	string str = "XorAgent: ";

	str.append("status=" + (m_alive ? to_string(1) : to_string(0)));
	str.append(" Genome: [");

	double checkSum = 0;
	for(size_t i = 0; i < 4; i++) {
		str.append(std::to_string(m_genome->getGenes()[i]));
		checkSum += m_genome->getGenes()[i];
		if (i+1 != m_genome->getGenes().size()) {
			str.append(", ");
		}
	}
	str.append("...] Error: " + to_string(m_error) + " Fitness: " + to_string(m_genome->getFitness()) + "\n");
	str.append("\n");



	return str;
}

