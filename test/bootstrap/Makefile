bootstrap-build: bootstrap.cpp BootStrapFitnessCalculator.cpp BootStrapAgent.cpp BootStrapFitnessCalculator.cpp BootStrapAgentFactory.cpp
	g++ -o bootstrap $^ -L../../build/. -lai -std=c++11 -O3

bootstrap-clean:
	rm -f bootstrap

clean: bootstrap-clean

all: bootstrap-build
