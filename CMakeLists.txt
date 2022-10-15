cmake_minimum_required(VERSION 3.24)
project(important_urgent_matrix)

set(CMAKE_CXX_STANDARD 17)

find_package(unofficial-nana REQUIRED)
add_executable(important_urgent_matrix main.cpp)
target_link_libraries(important_urgent_matrix PRIVATE unofficial::nana::nana)