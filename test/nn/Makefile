nn-build: nn.cpp
	g++ -o nn $^ -L../../build/. -lai -std=c++11 -O3

nn-clean:
	rm -f nn

clean: nn-clean

all: nn-build
