cmake_minimum_required(VERSION 3.22)

project(05.homework)

add_executable(statistics
    main.cpp
	stat.cpp
	interface.h
)

set_target_properties(statistics PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)