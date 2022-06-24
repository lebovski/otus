cmake_minimum_required(VERSION 3.8)

project(functions CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


add_executable(pow pow.cpp)
add_executable(gcd_cin gcd_cin.cpp)
add_executable(args args.cpp)
add_executable(gcd gcd.cpp)
add_executable(swap_naive swap_naive.cpp)
add_executable(swap swap.cpp)
add_executable(minigrep minigrep.cpp)
add_executable(module module.cpp)
add_executable(hello hello.cpp)
add_executable(hanoi hanoi.cpp)
add_executable(fib fib.cpp)
