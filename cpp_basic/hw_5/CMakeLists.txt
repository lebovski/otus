cmake_minimum_required(VERSION 3.22)

project(03.homework)

add_executable(game
	main.cpp
	check_value.cpp
	high_scores.cpp
	argument.cpp
	random_value.cpp
	random_value.h
	check_value.h
	high_scores.h
	argument.h
)

set_target_properties(game PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
