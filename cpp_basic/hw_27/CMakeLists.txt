cmake_minimum_required(VERSION 3.22)

project(27.topk_words)

add_executable(topk_words 
    topk_words.cpp
)

add_executable(topk_words_original 
    topk_words_original.cpp
)

set_target_properties(topk_words PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)