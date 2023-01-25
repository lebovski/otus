SHELL := /bin/bash

check: hw2build hw5build hw8build hw9build hw11build

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

# hw_9 runners
hw9build:
	cmake -S ./hw_9 -B ./hw_9/build && \
	cmake --build ./hw_9/build

# hw_11 runners
hw11build:
	cmake -S ./hw_11 -B ./hw_11/build && \
	cmake --build ./hw_11/build && \
	./hw_11/build/container

hw13build:
	cmake -S ./hw_13 -B ./hw_13/build && \
	cmake --build ./hw_13/build && \
	./hw_13/build/test_list

lect3build:
	cmake -S ./lect_3 -B ./lect_3/build && \
	cmake --build ./lect_3/build

lect4build:
	cmake -S ./lect_4 -B ./lect_4/build && \
	cmake --build ./lect_4/build

lect13build:
	cmake -S ./lect_13/project_prebuilt_gtest -B ./lect_13/project_prebuilt_gtest/build && \
	cmake --build ./lect_13/project_prebuilt_gtest/build

lect22build:
	cmake -S ./lect_22 -B ./lect_22/build && \
	cmake --build ./lect_22/build

lect23build:
	cmake -S ./lect_23 -B ./lect_23/build && \
	cmake --build ./lect_23/build