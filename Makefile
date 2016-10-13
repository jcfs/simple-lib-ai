src-build:
	$(MAKE) -C src/ all

src-clean:
	$(MAKE) -C src/ clean

all: src-build

clean: src-clean
