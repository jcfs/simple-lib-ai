src-build:
	$(MAKE) -C src/ objects

src-clean:
	$(MAKE) -C src/ clean

all: src-build

clean: src-clean
