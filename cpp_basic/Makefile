SHELL := /bin/bash

check: hw2build hw5build hw8build

# hw_2 runners
hw2build:
	cmake -S ./hw_2 -B ./hw_2/build && \
	cmake --build ./hw_2/build && \
	./hw_2/build/hello_world

hw2analyze:
	intercept-build cmake \
		-S ./hw_2 \
		-B ./hw_2/build \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_C_COMPILER=/usr/bin/clang \
		-DCMAKE_CXX_COMPILER=/usr/bin/clang++ && \
	intercept-build make VERBOSE=1

# hw_5 runners
hw5build:
	cmake -S ./hw_5 -B ./hw_5/build && \
	cmake --build ./hw_5/build

# hw_8 runners
hw8build:
	cmake -S ./hw_8 -B ./hw_8/build && \
	cmake --build ./hw_8/build

lect3build:
	cmake -S ./lect_3 -B ./lect_3/build && \
	cmake --build ./lect_3/build

lect4build:
	cmake -S ./lect_4 -B ./lect_4/build && \
	cmake --build ./lect_4/build
