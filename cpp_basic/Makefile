SHELL := /bin/bash

# hw_2 runners
hw2build:
	cmake3 -S ./hw_2 -B ./hw_2/build && \
	cmake3 --build ./hw_2/build && \
	./hw_2/build/hello_world

hw2analyze:
	intercept-build cmake \
		-S ./hw_2 \
		-B ./hw_2/build \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_C_COMPILER=/usr/bin/clang \
		-DCMAKE_CXX_COMPILER=/usr/bin/clang++ && \
	intercept-build make VERBOSE=1
