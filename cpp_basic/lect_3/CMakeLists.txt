cmake_minimum_required(VERSION 3.22)
project(cpp_basic_202106_03)

add_executable(lec03_01_type_ranges_int    lec03_01_type_ranges_int.cpp)
add_executable(lec03_02_type_ranges_float  lec03_02_type_ranges_float.cpp)
add_executable(lec03_03_cin_cout           lec03_03_cin_cout.cpp)
add_executable(lec03_04_arithm_opr         lec03_04_arithm_operations.cpp)
add_executable(lec03_05_bool_logic         lec03_05_bool_logic.cpp)
add_executable(lec03_06_if                 lec03_06_if.cpp)
add_executable(lec03_07_switch             lec03_07_switch.cpp)
add_executable(lec03_08_while_do_loop      lec03_08_while_do_loop.cpp)
add_executable(lec03_09_for_loop           lec03_09_for_loop.cpp)
add_executable(lec03_10_file_io            lec03_10_file_io.cpp)
add_executable(lec03_xx_cast_int_float            lec03_xx_cast_int_float.cpp)

set_target_properties(lec03_01_type_ranges_int
                      lec03_02_type_ranges_float
                      lec03_03_cin_cout
                      lec03_04_arithm_opr
                      lec03_05_bool_logic
                      lec03_06_if 
                      lec03_07_switch
                      lec03_08_while_do_loop
                      lec03_09_for_loop
                      lec03_10_file_io
                      lec03_xx_cast_int_float
PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
