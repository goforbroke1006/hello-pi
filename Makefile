.PHONY: src

all: build

.ONESHELL:
build:
	mkdir -p cmake-build-debug
	cd cmake-build-debug
	cmake ..
	make
	cd ..

test:
	echo "no tests"
