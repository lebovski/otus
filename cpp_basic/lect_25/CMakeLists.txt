cmake_minimum_required(VERSION 3.5)

project(22.Exceptions)

find_package(Threads)

add_executable(join_deadlock join_deadlock.cpp)
set_target_properties(join_deadlock PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )
target_link_libraries(
        join_deadlock
        PRIVATE
        ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(linked_list linked_list.cpp)
set_target_properties(linked_list PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

add_executable(naive_thread_safe_linked_list naive_thread_safe_linked_list.cpp)
set_target_properties(naive_thread_safe_linked_list PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )
target_link_libraries(
        naive_thread_safe_linked_list
        PRIVATE
        ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(monitor_object monitor_object.cpp)
set_target_properties(monitor_object PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )
target_link_libraries(
        monitor_object
        PRIVATE
        ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(condition condition.cpp)
set_target_properties(condition PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )
target_link_libraries(
        condition
        PRIVATE
        ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(waiting_queue waiting_queue.cpp)
set_target_properties(waiting_queue PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )
target_link_libraries(
        waiting_queue
        PRIVATE
        ${CMAKE_THREAD_LIBS_INIT}
)
