src-build:
	$(MAKE) -C src/ all

src-clean:
	$(MAKE) -C src/ clean

test-build:
	$(MAKE) -C test/ all

test-clean:
	$(MAKE) -C test/ clean

test-run:
	$(MAKE) -C test/ test-run

all: src-build test-build test-run

clean: src-clean test-clean
