sin-build: sin.cpp SinFitnessCalculator.cpp SinAgent.cpp SinFitnessCalculator.cpp SinAgentFactory.cpp
	g++ -o sin $^ -L../../build/. -lai -std=c++11 -O3

sin-tester: tester.cpp SinFitnessCalculator.cpp SinAgent.cpp SinFitnessCalculator.cpp SinAgentFactory.cpp
	g++ -o tester $^ -L../../build/. -lai -std=c++11 -O3

sin-clean:
	rm -f sin

clean: sin-clean

all: sin-build sin-tester
