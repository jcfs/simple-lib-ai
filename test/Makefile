test-build:
	$(MAKE) -C tictactoe/ all
	$(MAKE) -C memory/ all
	$(MAKE) -C bootstrap/ all

test-clean:
	$(MAKE) -C tictactoe/ clean
	$(MAKE) -C memory/ clean
	$(MAKE) -C bootstrap/ clean

all: test-build

clean: test-clean
