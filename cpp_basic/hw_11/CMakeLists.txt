cmake_minimum_required(VERSION 3.22)

project(06.homework)

add_executable(container
    main.cpp
	src/sequence.hpp
	src/linked.hpp
	src/interface.h
)

set_target_properties(container PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)