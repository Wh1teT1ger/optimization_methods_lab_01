cmake_minimum_required(VERSION 3.16)
project(simplex_method)
project(simplex_method_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(simplex_method_lib STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/simplex_method.cpp
        )

add_executable(simplex_method sources/main.cpp)

target_include_directories(simplex_method
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
target_include_directories(simplex_method_lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

target_link_libraries(simplex_method simplex_method_lib)