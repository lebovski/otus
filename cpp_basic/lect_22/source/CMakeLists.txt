cmake_minimum_required(VERSION 3.5)

project(22.Exceptions)

add_executable(error_codes_basics error_codes_basics.cpp)
set_target_properties(error_codes_basics PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

add_executable(error_codes_classes error_codes_classes.cpp)
set_target_properties(error_codes_classes PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

add_executable(error_codes_advanced error_codes_advanced.cpp)
set_target_properties(error_codes_advanced PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

add_executable(exceptions_basics exceptions_basics.cpp)
set_target_properties(exceptions_basics PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

add_executable(exceptions_advanced exceptions_advanced.cpp)
set_target_properties(exceptions_advanced PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

add_executable(exceptions_usage exceptions_usage.cpp)
set_target_properties(exceptions_usage PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

add_executable(exceptions_std exceptions_std.cpp)
set_target_properties(exceptions_std PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

