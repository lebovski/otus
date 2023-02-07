cmake_minimum_required(VERSION 3.10)

project(dynamic-memory CXX)

file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(src_file ${SRC_FILES})
    get_filename_component(target ${src_file} NAME_WLE)
    add_executable(${target} ${src_file})
    list(APPEND TARGETS ${target})
    message("target added: ${target}")
endforeach(src_file ${SRC_FILES})

foreach(target ${TARGETS})
    target_compile_features(${target} PRIVATE cxx_std_17)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target} PRIVATE
            -g
            -Wall
            -Wextra
            -Werror
            -pedantic
            -fsanitize=address # only for debug and test builds!
        )
        target_link_options(${target} PRIVATE
            -fsanitize=address
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} PRIVATE
            /W4
            /WX
            /fsanitize=address # only for debug and test builds!
        )
        target_link_options(${target} PRIVATE
            /fsanitize=address # only for debug and test builds!
        )
    endif()
endforeach()
